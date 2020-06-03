/*
 * =====================================================================================
 *
 *  ZeldaOOL
 *
 *  Copyright (C) 2014-2020 Unarelith, Quentin Bazin <zelda.ool@unarelith.net>
 *
 *  This file is part of ZeldaOOL.
 *
 *  ZeldaOOL is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  ZeldaOOL is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with ZeldaOOL; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 *
 * =====================================================================================
 */
#include "ButtonComponent.hpp"
#include "ButtonFactory.hpp"
#include "ButtonLoader.hpp"

void ButtonLoader::load(tinyxml2::XMLElement *buttonElement, gk::Scene &scene) {
	u16 tileX = buttonElement->IntAttribute("tileX");
	u16 tileY = buttonElement->IntAttribute("tileY");

	gk::SceneObject &button = scene.addObject(ButtonFactory::create(tileX, tileY));
	auto &buttonComponent = button.get<ButtonComponent>();

	tinyxml2::XMLElement *tileChangeElement = buttonElement->FirstChildElement("tileChange");
	while(tileChangeElement) {
		u16 tileX = tileChangeElement->IntAttribute("tileX");
		u16 tileY = tileChangeElement->IntAttribute("tileY");

		u16 newID = tileChangeElement->IntAttribute("newID");

		buttonComponent.addTileChange(tileX, tileY, newID);

		tileChangeElement = tileChangeElement->NextSiblingElement("tileChange");
	}
}

