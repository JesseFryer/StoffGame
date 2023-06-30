#pragma once

#include "GLM/glm.hpp"
#include "vector"

class SpriteSheet
{
public:
	SpriteSheet(unsigned int sheetWidth, unsigned int sheetHeight, unsigned int tileWidth, unsigned int tileHeight);
	glm::vec4 GetTexCoords(unsigned int spriteIndexX, unsigned int spriteIndexY, unsigned int tilesWide, unsigned int tilesHigh);

	unsigned int GetTilesHigh();
	unsigned int GetTilesWide();
private:
	float texXIncrement;
	float texYIncrement;
	unsigned int tilesWide;
	unsigned int tilesHigh;
};
