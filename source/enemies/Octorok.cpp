/*
 * =====================================================================================
 *
 *       Filename:  Octorok.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/10/2014 21:39:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  
 *
 * =====================================================================================
 */
#include "HurtMovement.hpp"
#include "Octorok.hpp"
#include "OctorokMovement.hpp"
#include "SoundEffect.hpp"

Octorok::Octorok(u16 x, u16 y, u8 direction) {
	load(x, y, direction);
}

void Octorok::load(u16 x, u16 y, u8 direction) {
	Enemy::load("enemies-octorok", x, y, 16, 16, direction);
	
	addAnimation({4, 0}, 150);
	addAnimation({5, 1}, 150);
	addAnimation({6, 2}, 150);
	addAnimation({7, 3}, 150);
	
	setMovement<OctorokMovement>();
	
	addCollisionHandler(std::bind(&Character::mapCollisions, this));
	addCollisionHandler(std::bind(&Enemy::mapBordersCollisions, this));
	
	m_maxLife = 2;
	
	Battler::reset();
}

void Octorok::update() {
	if(!m_dead) {
		Battler::update();
		Movable::update();
	}
}

void Octorok::draw() {
	if(m_dead) return;
	
	if(m_hurt) {
		drawFrame(m_x, m_y, m_direction);
	}
	else if(m_moving && !m_blocked) {
		playAnimation(m_x, m_y, m_direction);
	}
	else {
		drawFrame(m_x, m_y, m_lastFrameDisplayed);
	}
}

void Octorok::hurtAction(s16 vx, s16 vy) {
	SoundEffect::play("enemyHit");
	
	setMovement<HurtMovement>(vx, vy, 0.8);
}
