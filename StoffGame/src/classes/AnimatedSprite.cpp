#include "AnimatedSprite.h"
#include <iostream>

// Constructors.
AnimatedSprite::AnimatedSprite()
{
	Sprite::Sprite();
	SetCurrentAnimation(IDLE);
}

// Update.
void AnimatedSprite::Update(float timestep)
{
	m_animationCumulator += m_animationSpeeds[m_currentAnimation] * timestep;
	m_animationIndex = (unsigned int)m_animationCumulator;
	if (m_animationIndex > m_animations[m_currentAnimation].size() - 1) Reset();
	SetTexCoords(m_animations[m_currentAnimation][m_animationIndex]);
}

// Setters.
void AnimatedSprite::SetCurrentAnimation(Animation animation)
{
	m_currentAnimation = animation;
}

void AnimatedSprite::AddAnimation(Animation animation, std::vector<glm::vec4> frames, float speed)
{
	m_animations[animation] = frames;
	m_animationSpeeds[animation] = speed;
}

// Helper.
void AnimatedSprite::Reset()
{
	m_animationCumulator = 0.0f;
	m_animationIndex = 0;
}
