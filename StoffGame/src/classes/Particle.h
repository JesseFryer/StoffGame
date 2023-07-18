#ifndef PARTICLE_H
#define PARTICLE_H

#include "Entity.h"
class Particle : public Entity
{
public:
	Particle();
	Particle(glm::vec2 position, glm::vec2 size, glm::vec4 colour, glm::vec2 veclocity);
	void Update(float timeStep);
	void Reset();
	bool IsAlive();

private:
	bool AliveTooLong();
	float m_aliveTime = 0.0f;
	bool m_alive = false;
};

#endif
