#pragma once

#include "renderer\Renderer.h"
#include "utils\UserInput.h"
#include "utils\SpriteSheet.h"
#include "classes\AnimatedSprite.h"

#include <vector>
#include <string>

class Game
{
private:
	Renderer2D m_renderer;
	GLFWwindow* m_window = m_renderer.GetWindow();
	UserInput m_userInput = UserInput(m_window);
	bool m_running = true;

	std::vector<Sprite*> m_sprites;
	std::vector<AnimatedSprite*> m_animatedSprites;
	std::unordered_map<std::string, float> m_textureIDs;
	std::unordered_map<std::string, SpriteSheet*> m_spriteSheets;

public:
	Game();
	~Game();
	void Run();

private:
	void NewGame();
	void LoadTextures();
	void HandleInput();
	void RenderFrame();
	void Update(float timeStep);
};
