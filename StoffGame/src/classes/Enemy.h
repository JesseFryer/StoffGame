#pragma once

#include "Player.h"
#include "HealthBar.h"

class Renderer2D;

class Enemy : public Entity
{
public:
	Enemy(glm::vec2 position);
	void Update(float timeStep) override;
	static void SetPlayerPointer(Player* player);
	void Damage(float dmg);
	bool IsDead();
	void Render(Renderer2D& renderer);
private:
	HealthBar m_healthBar = HealthBar(GetPosition());
};
