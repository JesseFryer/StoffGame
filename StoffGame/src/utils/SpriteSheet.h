#pragma once

#include "GLM/glm.hpp"
#include "vector"

class SpriteSheet
{
public:
	SpriteSheet(unsigned int sheetWidth, unsigned int sheetHeight, unsigned int tileWidth, unsigned int tileHeight);
	glm::vec4 GetTexCoords(unsigned int spriteIndexX, unsigned int spriteIndexY, unsigned int tilesWide, unsigned int tilesHigh, bool flipped);
	std::vector<glm::vec4> GetAnimation(std::vector<unsigned int> spriteIndices, bool flipped);

private:
	float m_texXIncrement;
	float m_texYIncrement;
	unsigned int m_tilesWide;
	unsigned int m_tilesHigh;
};
