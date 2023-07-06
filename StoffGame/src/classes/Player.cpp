#include "Player.h"

static float SPEED = 150.0f;
static float JUMP_STRENGTH = 2.0f;

Player::Player(UserInput* inputs) 
{
	m_inputs = inputs;
	Entity::Entity();
}

void Player::Update(float timeStep)
{
	float dx = 0.0f;  // no acceleration on horizontal movement.
	if (m_inputs->IsPressed(Key_D)) dx += SPEED * timeStep;
	if (m_inputs->IsPressed(Key_A)) dx -= SPEED * timeStep;
	Move(dx, 0.0f);

	float velY = 0.0f;
	if (m_inputs->IsPressed(Key_SPC) && m_canJump)
	{
		velY += JUMP_STRENGTH;
		m_canJump = false;
	}
	ChangeVelocity(0.0f, velY);
	Entity::Update(timeStep); // this will apply resultant velocity.
}
