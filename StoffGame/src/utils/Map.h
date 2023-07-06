#pragma once

#include "classes\Tile.h"
#include <vector>

/// 
/// Stores vector of tile types, they are stored top to bottom, so top row of tiles
/// will be at the front of the vector.
/// 
class Map
{
public:
	Map();
	Map(const char* filePath);
	std::vector<std::vector<TileType>> GetTiles(); // Index in vector corresponds to position.

private:
	std::vector< std::vector<TileType> > m_tiles;
};