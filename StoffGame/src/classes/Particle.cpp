#include "Particle.h"

const static float s_maxAliveTime = 3.0f; // 3 seconds.

Particle::Particle()
{
	SetCurrentAnimation(NONE);
	SetColour(glm::vec4(1.0f, 0.0f, 0.0f, 0.5f));
	SetGravity(-400.0f);
}

Particle::Particle(glm::vec2 position, glm::vec2 size, glm::vec4 colour, glm::vec2 velocity)
{
	SetPosition(position);
	SetSize(size);
	SetColour(colour);
	SetVelocity(velocity[0], velocity[1]);
}

void Particle::Update(float timeStep)
{
	m_aliveTime += timeStep;
	if (AliveTooLong()) m_alive = false; 

	SetVelocity(GetVelocityX() * 0.98f, GetVelocityY()); // slowly reduce x velocity.
	Entity::Update(timeStep);
}

void Particle::Reset()
{
	m_aliveTime = 0.0f;
	m_alive = true;
}

bool Particle::IsAlive()
{
	return m_alive;
}

bool Particle::AliveTooLong()
{
	if (m_aliveTime > s_maxAliveTime) return true;
	return false;
}
