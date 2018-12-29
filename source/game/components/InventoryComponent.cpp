/*
 * =====================================================================================
 *
 *       Filename:  InventoryComponent.cpp
 *
 *    Description:
 *
 *        Created:  18/05/2015 16:17:04
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <gk/resource/ResourceHandler.hpp>

#include "GameKey.hpp"
#include "InventoryComponent.hpp"

Weapon *InventoryComponent::addWeapon(const std::string &name) {
	for(u8 x = 0 ; x < 4 ; x++) {
		for(u8 y = 0 ; y < 4 ; y++) {
			if(!m_weapons[x][y]) {
				m_weapons[x][y] = &gk::ResourceHandler::getInstance().get<Weapon>("weapon-" + name);
				return m_weapons[x][y];
			}
		}
	}

	return nullptr;
}

void InventoryComponent::equipWeapon(u8 x, u8 y, gk::GameKey key) {
	Weapon *temp = m_weapons[x][y];

	if(key == GameKey::A) {
		m_weapons[x][y] = m_weaponA;
		m_weaponA = temp;
	}
	else if(key == GameKey::B) {
		m_weapons[x][y] = m_weaponB;
		m_weaponB = temp;
	}
}

