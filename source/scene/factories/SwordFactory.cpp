/*
 * =====================================================================================
 *
 *       Filename:  SwordFactory.cpp
 *
 *    Description:  
 *
 *        Created:  19/03/2015 22:34:30
 *
 *         Author:  Quentin Bazin, <gnidmoo@gmail.com>
 *
 * =====================================================================================
 */
#include "Sprite.hpp"
#include "SwordFactory.hpp"

#include "LifetimeComponent.hpp"
#include "PositionComponent.hpp"

SceneObject SwordFactory::create(float x, float y) {
	SceneObject object;
	object.set<LifetimeComponent>([](SceneObject &object) {
		return object.get<Sprite>().currentAnimation().finished();
	});
	
	auto &positionComponent = object.set<PositionComponent>(x, y, 16, 16);
	positionComponent.hitbox.reset(0, 0, 16, 16); // TODO
	
	auto &spriteComponent = object.set<Sprite>("animations-sword", 16, 16);
	
	std::vector<std::vector<std::pair<s16, s16>>> swordPosition = {
		{{-15,   0}, {-13,  15}, {-13,  15}, { -1,  16}, { -1,  16}, { -1,  16}, { -1,  14}},
		{{ -5, -15}, {  8, -12}, {  8, -12}, { 15,   1}, { 15,   1}, { 15,   1}, { 12,   1}},
		{{  5, -15}, { -8, -12}, { -8, -12}, {-15,   1}, {-15,   1}, {-15,   1}, {-12,   1}},
		{{ 14,   4}, { 12, -12}, { 12, -12}, {  0, -15}, {  0, -15}, {  0, -15}, {  0, -11}}
	};
	
	std::vector<std::pair<s16, s16>> spinAttackPosition = {
		{ -1,  16}, {-12,  12}, {-15,  1}, {-12, -12},
		{  0, -15}, { 11, -12}, { 15,  2}, { 13,  13}
	};
	
	// Swinging
	spriteComponent.addAnimation({ 0, 4, 4,  8,  8,  8}, swordPosition[0], 40);
	spriteComponent.addAnimation({ 1, 5, 5,  9,  9,  9}, swordPosition[1], 40);
	spriteComponent.addAnimation({ 2, 6, 6, 10, 10, 10}, swordPosition[2], 40);
	spriteComponent.addAnimation({ 3, 5, 5, 11, 11, 11}, swordPosition[3], 40);
	
	// Loading
	spriteComponent.addAnimation({12,  8}, {swordPosition[0][6]}, 60);
	spriteComponent.addAnimation({13,  9}, {swordPosition[1][6]}, 60);
	spriteComponent.addAnimation({14, 10}, {swordPosition[2][6]}, 60);
	spriteComponent.addAnimation({15, 11}, {swordPosition[3][6]}, 60);
	
	// SpinAttack
	spriteComponent.addAnimation({8, 4, 10, 6, 11, 5, 9, 7}, 50);
	
	return object;
}
