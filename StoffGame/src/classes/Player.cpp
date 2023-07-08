#include "Player.h"

static float SPEED = 150.0f;
static float JUMP_STRENGTH = 3.0f;

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
	Entity::Update(timeStep);
}

glm::vec4 Player::GetCollider()
{

	return glm::vec4(GetPosition()[0] + 4.0f, GetPosition()[1], 12.0f, 29.0f);
}
