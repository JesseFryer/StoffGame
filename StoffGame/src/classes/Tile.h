#pragma once

#include "Sprite.h"

enum TileType
{
	DEFAULT,
	EMPTY,
    TOP_LEFT,
	TOP_MID,
	TOP_RIGHT,
	MID_LEFT,
	MID_MID,
	MID_RIGHT,
	BOT_LEFT,
	BOT_MID,
	BOT_RIGHT
};

class Tile : public Sprite 
{
public:
	Tile(glm::vec2 position);
	Tile(glm::vec2 position, TileType type);

private:
	TileType m_type;
};
