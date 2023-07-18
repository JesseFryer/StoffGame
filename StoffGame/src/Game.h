#pragma once

#include "renderer\Renderer.h"
#include "utils\UserInput.h"
#include "utils\SpriteSheet.h"
#include "classes\Player.h"
#include "classes\Enemy.h"
#include "classes\Bullet.h"
#include "utils\Map.h"

#include <vector>
#include <string>

class Game
{
public:
	Game();
	~Game();
	void Run();

private:
	void NewGame();
	void LoadMap(const char* filePath, std::string mapName);
	void UseMap(std::string mapName);
	void LoadTextures();
	void HandleInput();
	void RenderFrame();
	void Update(float timeStep);
	bool HasCollided(glm::vec4 rect1, glm::vec4 rect2);
	void EntityTileCollisions(float timeStep);
	void BulletTileCollisions();
	void Reset();

private:
	bool m_running = true;

	Renderer2D m_renderer;
	GLFWwindow* m_window = m_renderer.GetWindow();
	UserInput m_userInput = UserInput(m_window);

	Player* m_player = nullptr;
	std::vector<Entity*> m_entities;
	std::vector<Tile*> m_tiles;
	std::vector<Bullet*> m_bullets;

	std::unordered_map<std::string, float> m_textureIDs;
	std::unordered_map<TileType, glm::vec4> m_tileTexCoords;
	std::unordered_map<std::string, SpriteSheet*> m_spriteSheets;
	std::unordered_map<std::string, Map> m_maps;
};