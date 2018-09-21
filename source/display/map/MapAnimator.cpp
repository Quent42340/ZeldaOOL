/*
 * =====================================================================================
 *
 *       Filename:  MapAnimator.cpp
 *
 *    Description:
 *
 *        Created:  30/04/2015 19:46:41
 *
 *         Author:  Quentin Bazin, <gnidmoo@gmail.com>
 *
 * =====================================================================================
 */
#include "Map.hpp"
#include "MapAnimator.hpp"

void MapAnimator::updateTile(u16 tileX, u16 tileY, u16 tileID, const Tileset &tileset) {
	for(auto &it : tileset.anims()) {
		for(auto &n : it.frames) {
			if(tileID == n) {
				m_animatedTiles.emplace_back(tileX, tileY, n + 1 % it.frames.size(), it);
			}
		}
	}
}

void MapAnimator::animateTiles(Map &map) {
	for(auto &it : m_animatedTiles) {
		if(!it.timer.isStarted()) {
			it.timer.start();
		}

		if(it.timer.time() >= it.anim.delay) {
			map.setTile(it.tileX, it.tileY, it.anim.frames[it.nextFrame % it.anim.frames.size()]);

			it.nextFrame++;

			it.timer.reset();
			it.timer.start();
		}
	}
}

