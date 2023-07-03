#pragma once

#include "renderer\Renderer.h"
#include "utils\UserInput.h"
#include "classes\AnimatedSprite.h"

#include <vector>

class Game
{
private:
	Renderer2D renderer;
	GLFWwindow* window = renderer.GetWindow();
	UserInput userInput = UserInput(window);

	std::vector<Sprite*> m_sprites;
	std::vector<AnimatedSprite*> m_animatedSprites;

public:
	Game();
	void Run();

private:
	void NewGame();
};
