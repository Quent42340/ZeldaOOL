/*
 * =====================================================================================
 *
 *       Filename:  Scene.hpp
 *
 *    Description:  
 *
 *        Created:  15/02/2015 12:45:05
 *       Compiler:  gcc
 *
 *         Author:  Quentin Bazin, <gnidmoo@gmail.com>
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <utility>
#include <vector>

#include "DrawingSystem.hpp"
#include "MovementSystem.hpp"
#include "SceneObject.hpp"

class Scene {
	public:
		void update();
		
		void draw();
		
		void addObject(SceneObject &&object) { m_objects.push_back(std::move(object)); }
		
	private:
		DrawingSystem m_drawingSystem;
		
		MovementSystem m_movementSystem;
		
		std::vector<SceneObject> m_objects;
};

#endif // SCENE_HPP_
