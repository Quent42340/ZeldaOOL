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
#ifndef LIFETIMECONTROLLER_HPP_
#define LIFETIMECONTROLLER_HPP_

#include <gk/scene/controller/AbstractController.hpp>
#include <gk/scene/SceneObject.hpp>
#include <gk/scene/SceneObjectList.hpp>

class LifetimeController : public gk::AbstractController {
	public:
		void update(gk::SceneObject &) override {}
		void update(gk::SceneObjectList &objects) override;

		bool isGlobal() const override { return true; }
};

#endif // LIFETIMECONTROLLER_HPP_
