#pragma once

#include "Entity.h"
#include "utils\UserInput.h"

class Player : public Entity
{
public:
	Player(UserInput* inputs);
	void Update(float timeStep) override;
	
	glm::vec4 GetCollider() override;

private:
	UserInput* m_inputs = nullptr;
};