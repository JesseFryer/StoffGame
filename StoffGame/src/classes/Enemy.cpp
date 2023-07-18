#include "Enemy.h"
#include <iostream>

static Player* s_player = nullptr; // All enemies will have access to player info.
static float s_speed = 50.0f;

Enemy::Enemy(glm::vec2 position)
{
	SetPosition(position);
	SetSize(glm::vec2(15.0f));
}

void Enemy::Update(float timeStep)
{
	float dVelX = 0.0f;
	float dVelY = 0.0f;

	// Basic logic to follow player.
	if (s_player->GetPosition()[0] > GetPosition()[0]) dVelX += s_speed * timeStep;
	if (s_player->GetPosition()[0] < GetPosition()[0]) dVelX -= s_speed * timeStep;
	SetVelocity(dVelX, GetVelocityY()); // No acceleration on x moevement.
	Entity::Update(timeStep);
}

void Enemy::SetPlayerPointer(Player* player)
{
	s_player = player;
}
