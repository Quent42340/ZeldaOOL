/*
 * =====================================================================================
 *
 *       Filename:  MovementSystem.hpp
 *
 *    Description:  
 *
 *        Created:  14/02/2015 19:59:04
 *
 *         Author:  Quentin Bazin, <gnidmoo@gmail.com>
 *
 * =====================================================================================
 */
#ifndef MOVEMENTSYSTEM_HPP_
#define MOVEMENTSYSTEM_HPP_

#include "SceneObject.hpp"

class MovementSystem {
	public:
		static void process(SceneObject &object);
};

#endif // MOVEMENTSYSTEM_HPP_
