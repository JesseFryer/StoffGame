#include "Player.h"

static float SPEED = 150.0f;
static float JUMP_STRENGTH = 3.0f;
static float TIME_PER_SHOT = 0.1f; // 0.1 seconds.

Player::Player(UserInput* inputs) 
{
	m_inputs = inputs;
	Entity::Entity();
}
void Player::Update(float timeStep)
{
	float velX = 0.0f;
	if (m_inputs->IsPressed(Key_D)) velX += SPEED * timeStep;
	if (m_inputs->IsPressed(Key_A)) velX += -SPEED * timeStep;

	float velY = 0.0f;
	if (m_inputs->IsPressed(Key_SPC) && CanJump())
	{
		velY = JUMP_STRENGTH;
		SetCantJump();
	}
	ChangeVelocity(0.0f, velY);
	SetVelocity(velX, GetVelocityY()); // No acceleration on x moevement.

	m_shootAccumulator += timeStep;
	if (m_shootAccumulator > TIME_PER_SHOT) m_canShoot = true;
	Entity::Update(timeStep);
}

glm::vec4 Player::GetCollider()
{

	return glm::vec4(GetPosition()[0] + 4.0f, GetPosition()[1], 12.0f, 29.0f);
}
bool Player::CanShoot()
{
	return m_canShoot;
}
void Player::Shoot()
{
	m_canShoot = false;
	m_shootAccumulator = 0.0f;
}
