/*
 * =====================================================================================
 *
 *       Filename:  InventoryComponent.hpp
 *
 *    Description:
 *
 *        Created:  15/05/2015 19:15:32
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef INVENTORYCOMPONENT_HPP_
#define INVENTORYCOMPONENT_HPP_

#include <array>
#include <string>

#include "GameKey.hpp"
#include "Image.hpp"
#include "ResourceHandler.hpp"
#include "Translator.hpp"

class Item {
	public:
		Item(const std::string &name)
			: m_icon("icons-" + name), m_name(_t(name)), m_description(_t(name + "_description")) {}

		Image &icon() { return m_icon; }

		std::string name() const { return m_name; }
		std::string description() const { return m_description; }

	private:
		Image m_icon;

		std::string m_name;
		std::string m_description;
};

class Weapon : public Item {
	public:
		Weapon(const std::string &name, u8 strength = 0)
			: Item(name), m_strength(strength) {}

		u8 strength() const { return m_strength; }

	private:
		u8 m_strength = 0;
};

class InventoryComponent {
	public:
		Weapon *addWeapon(const std::string &name);
		Weapon *getWeapon(u8 x, u8 y) { return m_weapons[x][y]; }
		void removeWeapon(u8 x, u8 y) { m_weapons[x][y] = nullptr; }

		void equipWeapon(u8 x, u8 y, GameKey key);

		Weapon *getWeaponA() { return m_weaponA; }
		Weapon *getWeaponB() { return m_weaponB; }

		void addRupees(u16 rupees) { m_rupees = (m_rupees + rupees > 999) ? 999 : m_rupees + rupees; }
		void removeRupees(u16 rupees) { m_rupees = (m_rupees - rupees < 0) ? 0 : m_rupees - rupees; }

		u16 rupees() const { return m_rupees; }

	private:
		// NOTE: The '{}' are here to value-initialize the pointers (extra braces are needed until C++14)
		std::array<std::array<Weapon*, 4>, 4> m_weapons{{{{}}, {{}}, {{}}, {{}}}};

		Weapon *m_weaponA = nullptr;
		Weapon *m_weaponB = nullptr;

		u16 m_rupees = 197;
};

#endif // INVENTORYCOMPONENT_HPP_
