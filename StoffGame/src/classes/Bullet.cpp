#include "Bullet.h"

static float BULLET_SPEED = 6.0f;

Bullet::Bullet()
{
	m_xDir = 0.0f;
	m_yDir = 0.0f;
	SetSize(glm::vec2(5.0f));
	SetColour(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

void Bullet::Update(float timeStep)
{
	m_aliveTime += timeStep;
	if (AliveTooLong()) m_isActive = false;
	else
	{
		float dx = BULLET_SPEED * m_xDir;
		float dy = BULLET_SPEED * m_yDir;
		Move(dx, dy);
	}
}

float Bullet::GetXDirection()
{
	return m_xDir;
}

bool Bullet::IsActive()
{
	return m_isActive;
}

void Bullet::SetInactive()
{
	m_isActive = false;
}

void Bullet::SetActive()
{
	m_isActive = true;
	m_aliveTime = 0.0f;
}

void Bullet::SetUnitVector(glm::vec2 vector)
{
	m_xDir = vector[0];
	m_yDir = vector[1];
}

bool Bullet::AliveTooLong()
{
	if (m_aliveTime > 1.0f) return true; // 2 seconds.
	return false;
}
