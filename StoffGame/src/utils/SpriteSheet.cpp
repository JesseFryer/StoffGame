#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(unsigned int sheetWidth, unsigned int sheetHeight, unsigned int tileWidth, unsigned int tileHeight)
{
	m_texXIncrement = static_cast<float>(tileWidth) / sheetWidth;
	m_texYIncrement = static_cast<float>(tileHeight) / sheetHeight;
	m_tilesWide = sheetWidth / tileWidth;
	m_tilesHigh = sheetHeight / tileHeight;
}
glm::vec4 SpriteSheet::GetTexCoords(unsigned int spriteIndexX, unsigned int spriteIndexY, unsigned int tilesWide, unsigned int tilesHigh, bool flipped)
{
	float x1 = spriteIndexX * m_texXIncrement;
	float x2 = x1 + (tilesWide * m_texXIncrement);
	float y1 = spriteIndexY * m_texYIncrement;
	float y2 = y1 + (tilesHigh * m_texYIncrement);
	glm::vec4 texCoords;
	flipped ? texCoords = glm::vec4(x2, y1, x1, y2) : texCoords = glm::vec4(x1, y1, x2, y2);
	return texCoords;
}
std::vector<glm::vec4> SpriteSheet::GetAnimation(std::vector<unsigned int> spriteIndices, bool flipped)
{
	std::vector<glm::vec4> animation;

	unsigned int totalTilesInSheet = m_tilesHigh * m_tilesWide;
	for (unsigned int spriteIndex : spriteIndices)
	{
		unsigned int row = spriteIndex / m_tilesWide;
		unsigned int col = spriteIndex % m_tilesWide;
		animation.push_back(GetTexCoords(col, row, 1, 1, flipped));
	}
	return animation;
}
