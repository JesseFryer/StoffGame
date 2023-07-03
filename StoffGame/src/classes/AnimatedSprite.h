#pragma once

#include "Sprite.h"
#include <unordered_map>
#include <vector>

enum Animation
{
	IDLE
};

/// 
/// Animated Sprite holds an expandable map of animations.
/// The Update method cycles through animation frames and sets the current frame's
/// texture coordinates upstream to Sprite for rendering.  
/// 
class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite();
	void Update(float timestep);
	void SetCurrentAnimation(Animation animation);
	void AddAnimation(Animation animation, std::vector<glm::vec4> frames);

private:
	float m_animationCumulator;
	unsigned int m_animationIndex;
	std::unordered_map< Animation, std::vector<glm::vec4> > m_animations;
	std::unordered_map< Animation, float > m_animationSpeeds;
	Animation m_currentAnimation;

private:
	void Reset();
};
