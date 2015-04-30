/*
 * =====================================================================================
 *
 *       Filename:  GrassObject.hpp
 *
 *    Description:  
 *
 *        Created:  07/10/2014 15:33:51
 *
 *         Author:  Quentin Bazin, <gnidmoo@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GRASSOBJECT_HPP_
#define GRASSOBJECT_HPP_

#include "MapObject.hpp"

class GrassObject : public MapObject {
	public:
		GrassObject(float x, float y, bool lowGrass = false);
		
		void reset(Map &map);
		
		void draw();
		
		void onEvent(u8 event);
		
	private:
		Sprite m_grassDestroy{"animations-grassDestroy", 32, 32};
		
		bool m_cutted = false;
		
		bool m_lowGrass = false;
};

#endif // GRASSOBJECT_HPP_
