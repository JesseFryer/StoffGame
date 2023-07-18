#pragma once

#include "Entity.h"
#include "utils\UserInput.h"

class Player : public Entity
{
public:
	Player(UserInput* inputs);
	void Update(float timeStep) override;
	
	glm::vec4 GetCollider() override;
	bool CanShoot();
	void Shoot();

private:
	UserInput* m_inputs = nullptr;
	bool m_canShoot = true;
	float m_shootAccumulator = 0.0f;
};