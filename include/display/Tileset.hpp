/*
 * =====================================================================================
 *
 *       Filename:  Tileset.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  15/09/2014 20:59:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#ifndef TILESET_HPP_
#define TILESET_HPP_

#include "Texture.hpp"
#include "TileAnimation.hpp"

struct Tileset {
	Tileset() {}
	
	Tileset(std::string filename, u16 *_info, u16 _tileWidth = 16, u16 _tileHeight = 16) {
		texture.load(filename);
		
		info = _info;
		
		tileWidth  = _tileWidth;
		tileHeight = _tileHeight;
	};
	
	void addAnimation(std::initializer_list<u16> frames, u16 delay) {
		anims.push_back(TileAnimation(delay));
		
		for(auto &it : frames) {
			anims.back().frames.push_back(it);
		}
	}
	
	Texture texture;
	
	u16 *info;
	
	u16 tileWidth;
	u16 tileHeight;
	
	std::vector<TileAnimation> anims;
};

#endif // TILESET_HPP_
