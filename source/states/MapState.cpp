/*
 * =====================================================================================
 *
 *       Filename:  MapState.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  15/07/2014 14:00:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include <cmath>

#include "Debug.hpp"
#include "TimeManager.hpp"
#include "Application.hpp"
#include "CharacterManager.hpp"
#include "MapState.hpp"

MapState::MapState(State *parent) : State(parent) {
	m_mode = Mode::Normal;
	
	m_mapView.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	
	m_nextMap = nullptr;
	m_scrolled = 0;
	
	MapManager::init();
}

MapState::~MapState() {
}

void MapState::scrollMaps(double vx, double vy) {
	if(!m_nextMap) {
		m_nextMap = &MapManager::maps[MapManager::currentMap->area()][MapManager::currentMap->x() + vx + (MapManager::currentMap->y() + vy) * sqrt(MapManager::maps[MapManager::currentMap->area()].size())];
		
		m_nextMap->update();
		m_nextMap->setPosition(MapManager::currentMap->width() * 16 * vx, MapManager::currentMap->height() * 16 * vy);
		
		Sprite::pause = true;
	}
	
	vx *= 60 * TimeManager::dt;
	vy *= 60 * TimeManager::dt;
	
	CharacterManager::player.move(4.6 * -vx, 4.25 * -vy);
	m_mapView.move(5 * vx, 5 * vy);
	m_scrolled++;

}

void MapState::update() {
	if(m_mode == Mode::Normal) {
		CharacterManager::player.move();
		
		if(CharacterManager::player.x() < -3) {
			m_mode = Mode::ScrollingLeft;
		}
		else if(CharacterManager::player.x() + 13 > MapManager::currentMap->width() * 16) {
			m_mode = Mode::ScrollingRight;
		}
		else if(CharacterManager::player.y() < 15) {
			m_mode = Mode::ScrollingUp;
		}
		else if(CharacterManager::player.y() + 15 > MapManager::currentMap->height() * 16 + 16) {
			m_mode = Mode::ScrollingDown;
		}
	}
	
	if(m_mode == Mode::ScrollingLeft) {
		scrollMaps(-1, 0);
	}
	else if(m_mode == Mode::ScrollingRight) {
		scrollMaps(1, 0);
	}
	else if(m_mode == Mode::ScrollingUp) {
		scrollMaps(0, -1);
	}
	else if(m_mode == Mode::ScrollingDown) {
		scrollMaps(0, 1);
	}
	
	if((m_scrolled >= WINDOW_WIDTH / 5
	 && (m_mode == Mode::ScrollingLeft || m_mode == Mode::ScrollingRight))
	|| (m_scrolled >= WINDOW_HEIGHT / 5 - 2.5
	 && (m_mode == Mode::ScrollingUp || m_mode == Mode::ScrollingDown))) {
		MapManager::currentMap = m_nextMap;
		MapManager::currentMap->setPosition(0, 0);
		
		m_nextMap = nullptr;
		m_scrolled = 0;
		
		Sprite::pause = false;
		
		if(m_mode == Mode::ScrollingLeft) {
			CharacterManager::player.setPosition(CharacterManager::player.x() + m_scrolled * 4.6, CharacterManager::player.y());
		}
		else if(m_mode == Mode::ScrollingRight) {
			CharacterManager::player.setPosition(CharacterManager::player.x() - m_scrolled * 4.6, CharacterManager::player.y());
		}
		else if(m_mode == Mode::ScrollingUp) {
			CharacterManager::player.setPosition(CharacterManager::player.x(), CharacterManager::player.y() + m_scrolled * 4.25);
		}
		else if(m_mode == Mode::ScrollingDown) {
			CharacterManager::player.setPosition(CharacterManager::player.x(), CharacterManager::player.y() - m_scrolled * 4.25);
		}
		
		m_mapView.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
		
		m_mode = Mode::Normal;
	}
}

void MapState::render() {
	Application::window.setView(m_mapView);
	
	MapManager::currentMap->draw();
	
	if(m_mode == Mode::ScrollingLeft
	|| m_mode == Mode::ScrollingRight
	|| m_mode == Mode::ScrollingUp
	|| m_mode == Mode::ScrollingDown) {
		if(m_nextMap) m_nextMap->draw();
	}
	
	Application::window.setView(Application::window.getDefaultView());
	
	CharacterManager::player.draw();
	
	m_statsBar.draw();
}

