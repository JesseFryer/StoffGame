#include "Entity.h"


static float SPEED = 300.0f;
static float GRAVITY = -800.0f;
static float MAX_FALL_SPEED = -1200.0f;

Entity::Entity()
{
	m_gravity = GRAVITY;
}
Entity::Entity(glm::vec2 position)
{
	SetPosition(position);
}
void Entity::Update(float timeStep)
{
	ApplyGravity(timeStep);
	if (m_velY < MAX_FALL_SPEED) m_velY = MAX_FALL_SPEED;
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

bool Entity::CanJump()
{
	return m_canJump;
}

glm::vec4 Entity::GetCollider()
{
	return GetRect();
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
void Entity::SetCantJump()
{
	m_canJump = false;
}
void Entity::SetCanJump()
{
	m_canJump = true;
}
void Entity::ApplyGravity(float timeStep)
{
	m_velY += m_gravity * timeStep;
	if (m_velY < MAX_FALL_SPEED) m_velY = MAX_FALL_SPEED;
}
