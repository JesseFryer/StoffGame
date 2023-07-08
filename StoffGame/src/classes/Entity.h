#pragma once
#include "AnimatedSprite.h"

class Entity : public AnimatedSprite
{
public:
	Entity();
	Entity(glm::vec2 position);
	virtual void Update(float timeStep);

	float GetVelocityX();
	float GetVelocityY();
	bool CanJump();
	virtual glm::vec4 GetCollider();

	void ChangeVelocity(float dVelX, float dVelY);
	void SetVelocity(float velX, float velY);
	void SetGravity(float gravity);
	void SetCanJump();
	void SetCantJump();

private:
	void ApplyGravity(float timeStep);

private:
	float m_velX = 0.0f;
	float m_velY = 0.0f;
	float m_gravity;
	bool m_canJump = true;
};