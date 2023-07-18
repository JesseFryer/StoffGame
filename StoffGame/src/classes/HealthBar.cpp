#include "HealthBar.h"
#include <iostream>

const static float s_barWidth = 16.0f;
const static float s_barHeight = 2.0f;
const static float s_maxHp = 100.0f;

HealthBar::HealthBar(glm::vec2 position)
{
	m_hp = s_maxHp;

	m_healthBar.SetPosition(position);
	m_healthBar.SetSize(glm::vec2(s_barWidth, s_barHeight));
	m_healthBar.SetColour(glm::vec4(1.0f, 0.0f, 0.0f, 0.7f)); // red backround.

	m_currentHpBar.SetPosition(position);
	m_currentHpBar.SetSize(glm::vec2(s_barWidth, s_barHeight));
	m_currentHpBar.SetColour(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)); // green hp bar.
}

float HealthBar::GetHealth()
{
	return m_hp;
}

void HealthBar::SetHealth(float hp)
{
	m_hp = hp;
}

void HealthBar::ChangeHealthBy(float hp)
{
	m_hp += hp;
}


void HealthBar::Update()
{
	m_healthBar.SetPosition(GetPosition());
	m_currentHpBar.SetPosition(GetPosition());
	m_currentHpBar.SetSize(glm::vec2(GetSize()[0] * (m_hp / s_maxHp), s_barHeight));
}

void HealthBar::Render(Renderer2D& renderer)
{
	m_healthBar.Render(renderer);
	m_currentHpBar.Render(renderer);
}
