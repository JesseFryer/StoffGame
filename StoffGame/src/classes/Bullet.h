#pragma once

#include "AnimatedSprite.h"

class Bullet : public AnimatedSprite
{
public:
	Bullet();
	void Update(float timeStep);
	float GetXDirection();
	bool IsActive();
	void SetInactive();
	void SetActive();
	void SetUnitVector(glm::vec2 vector);

private:
	bool AliveTooLong();
	float m_xDir;
	float m_yDir;
	float m_aliveTime = 0.0f;
	bool m_isActive = false;
};
