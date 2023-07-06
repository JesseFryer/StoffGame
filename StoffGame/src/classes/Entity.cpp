#include "Entity.h"


static float SPEED = 100.0f;
static float GRAVITY = -0.6f;
static float MAX_FALL_SPEED = -100.0f;

Entity::Entity()
{
	m_gravity = GRAVITY;
}
void Entity::Update(float timeStep)
{
	ApplyGravity(timeStep);
	Move(m_velX, m_velY);
	AnimatedSprite::Update(timeStep);
}

float Entity::GetVelocityX()
{
	return m_velX;
}
float Entity::GetVelocityY()
{
	return m_velY;
}

void Entity::ChangeVelocity(float dVelX, float dVelY)
{
	m_velX += dVelX;
	m_velY += dVelY;
}
void Entity::SetVelocity(float velX, float velY)
{
	m_velX = velX;
	m_velY = velY;
}
void Entity::SetGravity(float gravity)
{
	m_gravity = gravity;
}
void Entity::ApplyGravity(float timeStep)
{
	m_velY += m_gravity * timeStep;
	if (m_velY < MAX_FALL_SPEED) m_velY = MAX_FALL_SPEED;
}
