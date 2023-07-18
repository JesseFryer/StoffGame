#ifndef HEALTH_BAR_H
#define HEALTH_BAR_H

#include "Sprite.h"
#include "GLM\glm.hpp"

class HealthBar : public Sprite
{
public:
	HealthBar(glm::vec2 position);
	float GetHealth();
	void SetHealth(float hp);
	void ChangeHealthBy(float hp);

	void Update();
	void Render(Renderer2D& renderer);
	
private:
	float m_hp;
	Sprite m_healthBar;
	Sprite m_currentHpBar;
};

#endif 

