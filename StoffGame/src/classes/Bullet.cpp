#include "Bullet.h"

static float BULLET_SPEED = 6.0f;

Bullet::Bullet(glm::vec2 position, glm::vec2 velocityVector)
{
	m_xDir = velocityVector[0];
	m_yDir = velocityVector[1];
	SetPosition(position);
	SetSize(glm::vec2(2.0f));
}

void Bullet::Update(float timeStep)
{
	m_aliveTime += timeStep;
	float dx = BULLET_SPEED * m_xDir;
	float dy = BULLET_SPEED * m_yDir;
	Move(dx, dy);
}

bool Bullet::AliveTooLong()
{
	if (m_aliveTime > 2.0f) return true; // 2 seconds.
	return false;
}
