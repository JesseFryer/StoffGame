#include "Player.h"

const static float SPEED = 200.0f;
const static float JUMP_STRENGTH = 300.0f;
const static float TIME_PER_SHOT = 0.1f; // 0.1 seconds.
static float KNOCKBACK = 300.0f;

Player::Player(UserInput* inputs) 
{
	m_inputs = inputs;
	Entity::Entity();
}
void Player::Update(float timeStep)
{
	m_healthBar.SetPosition(glm::vec2(GetPosition()[0] + 1.0f, GetPosition()[1] + GetSize()[1]));
	m_healthBar.Update();

	float velX = 0.0f;
	float velY = 0.0f;

	if (m_knocked)
	{
		m_knockTimeAccumulator += timeStep;
		if (m_knockTimeAccumulator > 0.5f)
		{
			m_knockTimeAccumulator = 0.0f;
			m_knockDirection = 0.0f;
			m_knocked = false;
		}
		velX += m_knockDirection * KNOCKBACK;
		KNOCKBACK *= 0.95f;
	}
	else
	{
		if (m_inputs->IsPressed(Key_D)) velX += SPEED;
		if (m_inputs->IsPressed(Key_A)) velX += -SPEED;
	}
	if (m_immune)
	{
		m_immuneTimeAccumulator += timeStep;
		if (m_immuneTimeAccumulator > 1.0f)
		{
			m_immune = false;
			m_immuneTimeAccumulator = 0.0f;
		}
	}
	if (m_inputs->IsPressed(Key_SPC))
	{
		if (CanJump())
		{
			velY = JUMP_STRENGTH;
			SetCantJump();
		}
		else if (!m_knocked)
		{
			SetGravity(-800.0f);
		}
	}
	else SetGravity(-1500.0f);
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
void Player::KnockBack(float direction)
{
	m_immune = true;
	m_knocked = true;
	m_knockDirection = direction;
	KNOCKBACK = 300.0f;
}
void Player::StopKnockBack()
{
	m_knocked = false;
	m_knockDirection = 0.0f;
	m_knockTimeAccumulator = 0.0f;
}
bool Player::IsImmune()
{
	return m_immune;
}
void Player::Damage(float dmg)
{
	m_healthBar.ChangeHealthBy(-dmg);
}
void Player::Render(Renderer2D& renderer)
{
	Sprite::Render(renderer);
	m_healthBar.Render(renderer);
}
