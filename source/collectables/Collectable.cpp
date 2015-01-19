/*
 * =====================================================================================
 *
 *       Filename:  Collectable.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/10/2014 17:19:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  
 *
 * =====================================================================================
 */
#include "CharacterManager.hpp"
#include "Collectable.hpp"
#include "Map.hpp"
#include "ResourceHandler.hpp"

Collectable::Collectable(const std::string &textureName, float x, float y) {
	load(textureName, x, y);
}

void Collectable::load(const std::string &textureName, float x, float y) {
	Texture &texture = ResourceHandler::getInstance().get<Texture>(textureName);
	
	MapObject::load(textureName, x + 7 - texture.width() / 2, y + 8 - texture.height(), texture.width(), texture.height());
}

void Collectable::update() {
	if(m_movementCounter < 5) {
		m_movementCounter += 0.25f;
		
		m_y += 0.25f;
	}
	else if(CharacterManager::player.inCollisionWith(*this)) {
		action();
		
		Map::currentMap->removeObject(*this);
	}
}

void Collectable::draw() {
	Image::draw(m_x, m_y);
}
