#pragma once
#include "renderer\Renderer.h"

/// 
/// Basic Sprite class which provides rendering functionality.
/// Empty constructor returns a sprite which will render as white square at (0, 0) 16p x 16p.
/// Holds an ID to a loaded texture to sample from.
/// Holds a texture coordinate which can be upated dynamically with SetTexCoords.   
/// 
class Sprite
{
public:
	Sprite();
	Sprite(glm::vec2 position);
	Sprite(glm::vec2 position, float texID);
	Sprite(glm::vec2 position, float texID, glm::vec4 texCoords);
	void Render(Renderer2D& renderer);

public:
	glm::vec2 GetPosition();
	glm::vec2 GetSize();

public:
	void Move(float dx, float dy);
	void SetPosition(glm::vec2 position);
	void SetSize(glm::vec2 size);
	void SetTexCoords(glm::vec4 texCoords);
	void SetTexID(float texID);

private:
	glm::vec2 m_position;
	glm::vec2 m_size;
	glm::vec4 m_texCoords;
	float m_texID;
};
