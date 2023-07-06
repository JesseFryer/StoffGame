#pragma once
#include "AnimatedSprite.h"

class Entity : public AnimatedSprite
{
public:
	Entity();
	void Update(float timeStep);

	float GetVelocityX();
	float GetVelocityY();

	void ChangeVelocity(float dVelX, float dVelY);
	void SetVelocity(float velX, float velY);
	void SetGravity(float gravity);

private:
	void ApplyGravity(float timeStep);

private:
	float m_velX = 0.0f;
	float m_velY = 0.0f;
	float m_gravity;
};