#include "Sprite.h"

// Default settings.
struct SpriteDefaults
{
	glm::vec2 i_position = glm::vec2(0.0f);
	glm::vec2 i_size = glm::vec2(16.0f);
	glm::vec4 i_texCoords = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	float i_texID = -1.0f;
};
static SpriteDefaults defaults;

// Constructors.
Sprite::Sprite()
{
	SetPosition(defaults.i_position);
	SetSize(defaults.i_size);
	SetTexCoords(defaults.i_texCoords);
	SetTexID(defaults.i_texID);  
}
Sprite::Sprite(glm::vec2 position)
{
	SetPosition(position);
	SetSize(defaults.i_size);
	SetTexCoords(defaults.i_texCoords);
	SetTexID(defaults.i_texID); 
}
Sprite::Sprite(glm::vec2 position, float texID)
{
	SetPosition(position);
	SetSize(defaults.i_size);
	SetTexCoords(defaults.i_texCoords);
	SetTexID(texID); 
}
Sprite::Sprite(glm::vec2 position, float texID, glm::vec4 texCoords)
{
	SetPosition(position);
	SetSize(defaults.i_size);
	SetTexCoords(texCoords);
	SetTexID(texID);
}

// Render.
void Sprite::Render(Renderer2D& renderer)
{
	// Render white quad if no texture has been set yet.
	if (m_texID == -1.0f) renderer.AddQuad(m_position, m_size, glm::vec4(1.0f));
	else renderer.AddQuad(m_position, m_size, m_texCoords, m_texID);
}

// Getters.
glm::vec2 Sprite::GetPosition()
{
	return m_position;
}
glm::vec2 Sprite::GetSize()
{
	return m_size;
}

// Setters.
void Sprite::Move(float dx, float dy)
{
	m_position[0] += dx;
	m_position[1] += dy;
}
void Sprite::SetPosition(glm::vec2 position)
{
	m_position = position;
}
void Sprite::SetSize(glm::vec2 size)
{
	m_size = size;
}
void Sprite::SetTexCoords(glm::vec4 texCoords)
{
	m_texCoords = texCoords;
}
void Sprite::SetTexID(float texID)
{
	m_texID = texID;
}
