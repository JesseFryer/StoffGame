#pragma once

#include "Player.h"

class Enemy : public Entity
{
public:
	Enemy(glm::vec2 position);
	void Update(float timeStep) override;
	static void SetPlayerPointer(Player* player);
};
