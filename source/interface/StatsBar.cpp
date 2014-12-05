/*
 * =====================================================================================
 *
 *       Filename:  StatsBar.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/12/2014 00:50:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  
 *
 * =====================================================================================
 */
#include <cmath>

#include "GameState.hpp"
#include "Player.hpp"
#include "StatsBar.hpp"

StatsBar::StatsBar() {
	m_background.load("stats");
	
	m_hearts.load("hearts", 7, 7);
	m_numbers.load("numbers", 7, 6);
}

StatsBar::~StatsBar() {
}

void StatsBar::draw() {
	m_background.draw(0, 0);
	
	u8 maxLife = Player::getInstance().maxLife();
	for(u8 j = 0 ; j <= maxLife / 28 ; j++) {
		for(u8 i = 0 ; i < maxLife / 4 - j * 7 && i < 7 ; i++) {
			s16 life = Player::getInstance().life() - j * 28;
			
			if(life > (i + 1) * 4) {
				m_hearts.drawFrame(104 + i * 8, j * 8, 4);
			}
			else if(i * 4 <= life) {
				m_hearts.drawFrame(104 + i * 8, j * 8, life - (i * 4));
			} else {
				m_hearts.drawFrame(104 + i * 8, j * 8, 0);
			}
		}
	}
	
	u16 rupees = GameState::getInstance().playerRupees();
	for(u8 i = 0 ; i <= log10(rupees) ; i++) {
		m_numbers.drawFrame(81 + 8 * i, 9, (rupees % (u16)pow(10, floor(log10(rupees) - i + 1))) / pow(10, floor(log10(rupees) - i)));
	}
}
