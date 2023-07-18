#pragma once

#include "AnimatedSprite.h"

class Bullet : public AnimatedSprite
{
public:
	Bullet(glm::vec2 position, glm::vec2 velocityVector);
	void Update(float timeStep);
	float GetXDirection();
	bool AliveTooLong();

private:
	float m_xDir;
	float m_yDir;
	float m_aliveTime = 0.0f;
};
