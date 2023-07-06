#include "Tile.h"

Tile::Tile(glm::vec2 position)
{
	SetPosition(position);
	m_type = DEFAULT;
}

Tile::Tile(glm::vec2 position, TileType type)
{
	SetPosition(position);
	m_type = type;
}
