/*
 * =====================================================================================
 *
 *       Filename:  PlayerGrabState.cpp
 *
 *    Description:
 *
 *        Created:  22/09/2018 19:59:03
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "GamePad.hpp"
#include "MovementComponent.hpp"
#include "SpriteComponent.hpp"
#include "StateComponent.hpp"
#include "PlayerGrabState.hpp"
#include "TilesInfos.hpp"
#include "WeaponComponent.hpp"
#include "World.hpp"

#include "PlayerMovingState.hpp"
#include "PlayerPushState.hpp"
#include "PlayerStandingState.hpp"

void PlayerGrabState::onBegin(SceneObject &object) {
	m_state = "Grab";

	auto &movement = object.get<MovementComponent>();
	movement.isDirectionLocked = true;
	movement.speed = 0;
}

void PlayerGrabState::onEnd(SceneObject &object) {
	auto &movement = object.get<MovementComponent>();
	movement.isDirectionLocked = false;
	movement.speed = 0.4f;
}

void PlayerGrabState::update(SceneObject &object) {
	auto &movement = object.get<MovementComponent>();
	auto &state = object.get<StateComponent>();

	if(m_state == "Grab") {
		if (movement.isMoving)
			m_state = "Pull";

		if (movement.speed != 0 || !GamePad::isKeyPressed(m_weapon->get<WeaponComponent>().key)) {
			state.setState<PlayerStandingState>(object);
		}
	}
	else if(m_state == "Pull") {
		if (!movement.isMoving)
			m_state = "Grab";

		if (movement.speed != 0 || !GamePad::isKeyPressed(m_weapon->get<WeaponComponent>().key)) {
			state.setState<PlayerStandingState>(object);
		}

		auto &positionComponent = object.get<PositionComponent>();
		if (World::getInstance().currentMap()->isTile(positionComponent.getFrontTile().x * 16,
		                                              positionComponent.getFrontTile().y * 16,
		                                              TilesInfos::Stone) && movement.isMoving)
		{
			movement.isDirectionLocked = false;
			movement.speed = 0.4f;
			m_state = "Lift";

			SceneObject tile("Tile");
			tile.set<PositionComponent>();
			tile.set<Sprite>("tilesets-plain", 16, 16).setCurrentFrame(World::getInstance().currentMap()->getTile(
				positionComponent.getFrontTile().x,
				positionComponent.getFrontTile().y
			));

			object.get<SceneObjectList>().addObject(std::move(tile));

			World::getInstance().currentMap()->setTile(positionComponent.getFrontTile().x,
			                                           positionComponent.getFrontTile().y, 36);
		}
	}
	else if(m_state == "Lift") {
		if (GamePad::isKeyPressedOnce(m_weapon->get<WeaponComponent>().key)) {
			object.get<SceneObjectList>().removeByName("Tile");
			state.setState<PlayerStandingState>(object);
		}
	}

	updateSprite(object);
}

void PlayerGrabState::updateSprite(SceneObject &object) {
	auto &movement = object.get<MovementComponent>();
	auto &sprite = object.get<SpriteComponent>();

	if (m_state == "Lift") {
		sprite.setAnimated(movement.isMoving);
	}

	PlayerState::updateSprite(object);
}
