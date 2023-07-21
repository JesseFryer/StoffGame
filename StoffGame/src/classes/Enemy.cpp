#include "Enemy.h"
#include <iostream>

static Player* s_player = nullptr; // All enemies will have access to player info.
static float s_acceleration = 5.0f;
const static float s_maxSpeed = 150.0f;

Enemy::Enemy(glm::vec2 position)
{
	SetPosition(position);
	SetSize(glm::vec2(15.0f));
}

void Enemy::Update(float timeStep)
{
	m_healthBar.SetPosition(glm::vec2(GetPosition()[0], GetPosition()[1] + GetSize()[1] + 5.0f));
	m_healthBar.Update();

	float dVelX = 0.0f;
	float dVelY = 0.0f;

	// Basic logic to follow player.
	if (s_player->GetPosition()[0] > GetPosition()[0]) dVelX += s_acceleration;
	if (s_player->GetPosition()[0] < GetPosition()[0]) dVelX -= s_acceleration;
	float velXResult = dVelX + GetVelocityX();
	if (GetVelocityY() == 0.0f)
	{
		if (velXResult > s_maxSpeed) velXResult = s_maxSpeed;
		if (velXResult < -s_maxSpeed) velXResult = -s_maxSpeed;
	}
	SetVelocity(velXResult, GetVelocityY()); 
	Entity::Update(timeStep);
}

void Enemy::SetPlayerPointer(Player* player)
{
	s_player = player;
}

void Enemy::Damage(float dmg)
{
	m_healthBar.ChangeHealthBy(-dmg);
}

bool Enemy::IsDead()
{
	if (m_healthBar.GetHealth() > 0.0f) return false;
	return true;
}

void Enemy::Render(Renderer2D& renderer)
{
	Sprite::Render(renderer);
	m_healthBar.Render(renderer);
}
