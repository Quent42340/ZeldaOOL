/*
 * =====================================================================================
 *
 *       Filename:  Enemy.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/10/2014 21:38:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef ENEMY_HPP_
#define ENEMY_HPP_

#include "Battler.hpp"

class Enemy : public Battler {
	public:
		Enemy();
		Enemy(std::string filename, u16 x, u16 y, u16 width, u16 height, u8 direction);
		
		void load(std::string filename, u16 x, u16 y, u16 width, u16 height, u8 direction);
		
		virtual void reset(Map &) override;
		
		void mapBordersCollisions();
		
		void checkDeath();
		
		u8 strength() const { return m_strength; }
		
		bool isDead() const { return m_dead; }
		
	protected:
		bool m_dead = false;
		
	private:
		u8 m_strength = 1;
};

#endif // ENEMY_HPP_