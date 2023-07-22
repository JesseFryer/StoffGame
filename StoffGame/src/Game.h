#pragma once

#include "renderer\Renderer.h"
#include "utils\UserInput.h"
#include "utils\SpriteSheet.h"
#include "classes\Player.h"
#include "classes\Enemy.h"
#include "classes\Bullet.h"
#include "classes\Particle.h"
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
	void Reset();

	void LoadMap(const char* filePath, std::string mapName);
	void UseMap(std::string mapName);
	void LoadTextures();

	void HandleInput();

	void Update(float timeStep);
	void RenderFrame();

	bool HasCollided(glm::vec4 rect1, glm::vec4 rect2);
	void EntityTileCollisions(float timeStep);
	void BulletTileCollisions(float timeStep);
	void ParticleTileCollisions(float timeStep);
	void BulletEnemyCollisions(float timeStep);
	void PlayerTileCollisions(float timeStep);
	void PlayerEnemyCollisions();

	void GenerateParticles(glm::vec2 position, unsigned int numOfParticles);

private:
	bool m_running = true;

	Renderer2D m_renderer;
	GLFWwindow* m_window = m_renderer.GetWindow();
	UserInput m_userInput = UserInput(m_window);

	Player* m_player = nullptr;
	std::vector<Enemy*> m_enemies; 
	std::vector<Tile> m_tiles;
	Bullet m_bullets[50];
	size_t m_bulletsIndex = 0; 
	Particle m_particles[1000];
	size_t m_particlesIndex = 0;

	std::unordered_map<std::string, float> m_textureIDs;
	std::unordered_map<TileType, glm::vec4> m_tileTexCoords;
	std::unordered_map<std::string, SpriteSheet*> m_spriteSheets;
	std::unordered_map<std::string, Map> m_maps;
};