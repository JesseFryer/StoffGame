#pragma once

#include "Entity.h"
#include "utils\UserInput.h"

class Player : public Entity
{
public:
	Player(UserInput* inputs);
	void Update(float timeStep);

private:
	UserInput* m_inputs = nullptr;
	bool m_canJump = true;
};