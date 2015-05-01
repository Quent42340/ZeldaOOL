/*
 * =====================================================================================
 *
 *       Filename:  Map.cpp
 *
 *    Description:  
 *
 *        Created:  30/04/2015 19:45:20
 *
 *         Author:  Quentin Bazin, <gnidmoo@gmail.com>
 *
 * =====================================================================================
 */
#include "GrassObject.hpp"
#include "Map.hpp"
#include "MapLoader.hpp"
#include "ResourceHandler.hpp"
#include "TilesData.hpp"

Map *Map::currentMap = nullptr;

Map::Map(u16 area, u16 x, u16 y, u16 width, u16 height, Tileset &tileset, const std::vector<u16> &data) : m_tileset(tileset) {
	m_area = area;
	m_x = x;
	m_y = y;
	
	m_width = width;
	m_height = height;
	
	m_baseData = data;
	m_data = data;
	
	m_view.reset(0, 16, m_width * tileset.tileWidth(), m_height * tileset.tileHeight());
	
	m_renderer.init(m_width, m_height);
	
	updateTiles();
}

void Map::update() {
	m_animator.animateTiles(*this);
	
	for(auto &it : m_objects) it->update();
}

void Map::draw() {
	View::bind(&m_view);
	
	m_renderer.draw(*this);
	
	for(auto &it : m_objects) it->draw();
	
	View::bind(nullptr);
}

void Map::resetTiles() {
	m_data = m_baseData;
}

void Map::updateTiles() {
	for(u16 tileY = 0 ; tileY < m_height ; tileY++) {
		for(u16 tileX = 0 ; tileX < m_width ; tileX++) {
			u16 tileID = getTile(tileX, tileY);
			
			m_renderer.updateTile(tileX, tileY, tileID, *this);
			m_animator.updateTile(tileX, tileY, tileID, m_tileset);
			
			u16 x = tileX * m_tileset.tileWidth();
			u16 y = tileY * m_tileset.tileHeight();
			
			if(m_tileset.info()[tileID] == TilesData::TileType::GrassTile) {
				addObject<GrassObject>(x, y);
			}
			else if(m_tileset.info()[tileID] == TilesData::TileType::LowGrassTile) {
				addObject<GrassObject>(x, y, true);
			}
		}
	}
}

u16 Map::getTile(u16 tileX, u16 tileY) {
	if(tileX + tileY * m_width < m_width * m_height) {
		return m_data[tileX + tileY * m_width];
	} else {
		return 0;
	}
}

void Map::setTile(u16 tileX, u16 tileY, u16 id) {
	if(tileX + tileY * m_width < m_width * m_height) {
		m_data[tileX + tileY * m_width] = id;
	}
	
	m_renderer.updateTile(tileX, tileY, id, *this);
}

bool Map::passable(float x, float y) {
	s16 tile = m_tileset.info()[getTile(x / m_tileset.tileWidth(),
	                                    y / m_tileset.tileHeight())];
	
	return TilesData::infos[tile][(s16(x) & 0xF) / (m_tileset.tileWidth()  / 2)
	                            + (s16(y) & 0xF) / (m_tileset.tileHeight() / 2) * 2] != TilesData::SubTileType::NonPassable;
}

bool Map::onDoor(float x, float y) {
	s16 tile = m_tileset.info()[getTile(x / m_tileset.tileWidth(),
	                                    y / m_tileset.tileHeight())];
	
	return TilesData::infos[tile][(s16(x) & 0xF) / (m_tileset.tileWidth()  / 2)
	                            + (s16(y) & 0xF) / (m_tileset.tileHeight() / 2) * 2] == TilesData::SubTileType::ChangeMap;
}

bool Map::isTile(float x, float y, u16 tile) {
	return m_tileset.info()[getTile(x / m_tileset.tileWidth(),
	                                y / m_tileset.tileHeight())] == tile;
}

Map &Map::getMap(u16 area, u16 mapX, u16 mapY) {
	return ResourceHandler::getInstance().get<Map>(MapLoader::makeName(area, mapX, mapY));
}

bool Map::mapExists(u16 area, u16 mapX, u16 mapY) {
	return ResourceHandler::getInstance().has(MapLoader::makeName(area, mapX, mapY));
}
