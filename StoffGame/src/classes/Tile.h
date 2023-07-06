#pragma once

#include "Sprite.h"

enum TileType
{
	DEFAULT
};

class Tile : public Sprite 
{
public:
	Tile(glm::vec2 position);
	Tile(glm::vec2 position, TileType type);

private:
	TileType m_type;
};
