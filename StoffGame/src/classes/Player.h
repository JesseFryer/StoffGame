#pragma once

#include "Entity.h"
#include "utils\UserInput.h"
#include "HealthBar.h"

class Player : public Entity
{
public:
	Player(UserInput* inputs);
	void Update(float timeStep) override;
	void Render(Renderer2D& renderer);
	glm::vec4 GetCollider() override;
	bool CanShoot();
	void Shoot();
	void KnockBack(float direction);
	void StopKnockBack();
	bool IsImmune();
	bool IsDead();
	void Damage(float dmg);
	void ResetHealth();

private:
	HealthBar m_healthBar = HealthBar(GetPosition());
	UserInput* m_inputs = nullptr;

	bool m_canShoot = true;
	float m_shootAccumulator = 0.0f;

	bool m_knocked = false;
	float m_knockTimeAccumulator = 0.0f;
	float m_knockDirection = 0.0f;

	bool m_immune = false;
	float m_immuneTimeAccumulator = 0.0f;

};