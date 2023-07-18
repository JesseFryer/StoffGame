#pragma once

#include "Game.h"
#include <iostream>
#include <chrono>
#include <thread>

struct Globals
{
	float MOUSE_SCROLL = 0.0f;
	const float MOUSE_SCROLL_SENSITIVITY = 0.1f;
	const float CAMERA_SPEED = 2.0f;
	const glm::vec2 SPAWN_POINT = glm::vec2(600.0f, 1000.0f);
	const double FRAME_CAP = 1.0 / 144.0;
};
static Globals globals;
void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	globals.MOUSE_SCROLL = ((float)yOffset) * globals.MOUSE_SCROLL_SENSITIVITY;
}

Game::Game()
{
	glfwSetScrollCallback(m_window, ScrollCallback);
	LoadTextures();
	LoadMap("res/maps/map1.txt", "map1");
	NewGame();
}
Game::~Game()
{
	for (Entity* entity : m_entities) delete entity;
	for (Tile* tile : m_tiles) delete tile;
	for (auto& pair : m_spriteSheets) delete pair.second;
}

void Game::Run()
{
	int logFpsCounter = 0;
	float lastTime = glfwGetTime();

	while (m_running)
	{
		HandleInput();

		logFpsCounter++;
		float currentTime = glfwGetTime();
		float timeStep = currentTime - lastTime;
		lastTime = currentTime;
		if (logFpsCounter > 100)
		{
			logFpsCounter = 0;
			std::cout << 1.0 / timeStep << "\n";
		}

		Update(timeStep);

		m_renderer.SetCameraPosition(m_player->GetCenter());
		m_renderer.ZoomCamera(globals.MOUSE_SCROLL);
		globals.MOUSE_SCROLL *= 0.95f; // Slowly decreases scroll value for smooth zooming in/out.

		RenderFrame();
	}
	glfwTerminate();
}

void Game::NewGame()
{
	Reset();

	m_player = new Player(&m_userInput);
	Enemy::SetPlayerPointer(m_player);

	Entity* coin = new Entity(glm::vec2(300.0f, 1000.0f));
	Enemy* enemy = new Enemy(glm::vec2(800.0f, 1000.0f));
	enemy->SetCurrentAnimation(NONE);

	m_entities.push_back(m_player);
	m_entities.push_back(coin);
	m_entities.push_back(enemy);
	
	coin->SetTexID(m_textureIDs["coin"]);
	std::vector<unsigned int> coinSpinFrames = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	coin->AddAnimation(IDLE, m_spriteSheets["coin"]->GetAnimation(coinSpinFrames, false), 36.0f);
	coin->SetCurrentAnimation(IDLE);
	coin->SetGravity(-10.0f);

	m_player->SetTexID(m_textureIDs["player"]);
	std::vector<unsigned int> playerIdleFrames = { 0, 1, 2, 3, 4, 5 };
	m_player->AddAnimation(IDLE, m_spriteSheets["player"]->GetAnimation(playerIdleFrames, false), 8.0f);
	m_player->SetCurrentAnimation(IDLE);
	m_player->SetSize(glm::vec2(20.0f, 32.0f));
	m_player->SetPosition(globals.SPAWN_POINT);

	UseMap("map1");
}
void Game::LoadMap(const char* filePath, std::string mapName)
{
	m_maps[mapName] = Map(filePath);
}
void Game::UseMap(std::string mapName)
{
	const float TILE_SIZE = 16.0f;

	// Clear old map.
	for (Tile* tile : m_tiles) delete tile;
	m_tiles.clear();

	std::vector<std::vector<TileType>> map = m_maps[mapName].GetTiles();
	float yPos = 0.0f;
	for (int i = map.size() - 1; i > -1; i--) // Go backwards becuase tiles are stored from top down.
	{
		float xPos = 0.0f;
		for (TileType type : map[i])
		{
			if (type != EMPTY)
			{
				Tile* tile = new Tile(glm::vec2(xPos, yPos), type);
				tile->SetTexID(m_textureIDs["tiles"]);
				tile->SetTexCoords(m_tileTexCoords[type]);
				m_tiles.push_back(tile);
			}
			xPos += TILE_SIZE;
		}
		yPos += TILE_SIZE;
	}
}
void Game::LoadTextures()
{
	m_textureIDs["player"] = m_renderer.LoadTexture("res/sprites/PlayerSpriteSheet.png");
	m_spriteSheets["player"] = new SpriteSheet(200, 320, 20, 32);
	m_textureIDs["coin"] = m_renderer.LoadTexture("res/sprites/coin.png");
	m_spriteSheets["coin"] = new SpriteSheet(208, 16, 16, 16);
	m_textureIDs["tiles"] = m_renderer.LoadTexture("res/sprites/TileSet.png");
	m_spriteSheets["tiles"] = new SpriteSheet(128, 128, 16, 16);
	m_tileTexCoords[TOP_LEFT]  = m_spriteSheets["tiles"]->GetTexCoords(0, 2, 1, 1, 0);
	m_tileTexCoords[TOP_MID]   = m_spriteSheets["tiles"]->GetTexCoords(1, 2, 1, 1, 0);
	m_tileTexCoords[TOP_RIGHT] = m_spriteSheets["tiles"]->GetTexCoords(2, 2, 1, 1, 0);
	m_tileTexCoords[MID_LEFT]  = m_spriteSheets["tiles"]->GetTexCoords(0, 1, 1, 1, 0);
	m_tileTexCoords[MID_MID]   = m_spriteSheets["tiles"]->GetTexCoords(1, 1, 1, 1, 0);
	m_tileTexCoords[MID_RIGHT] = m_spriteSheets["tiles"]->GetTexCoords(2, 1, 1, 1, 0);
	m_tileTexCoords[BOT_LEFT]  = m_spriteSheets["tiles"]->GetTexCoords(0, 0, 1, 1, 0);
	m_tileTexCoords[BOT_MID]   = m_spriteSheets["tiles"]->GetTexCoords(1, 0, 1, 1, 0);
	m_tileTexCoords[BOT_RIGHT] = m_spriteSheets["tiles"]->GetTexCoords(2, 0, 1, 1, 0);
}
void Game::HandleInput()
{
	glfwPollEvents();
	m_userInput.UpdateInputs();
	if (glfwWindowShouldClose(m_window) || m_userInput.IsPressed(Key_ESC)) m_running = false;
	if (m_userInput.LeftClick() && m_player->CanShoot()) 
	{
		m_player->Shoot();
		// Finding unit vector from center of screen/player to cursor to fire bullet in that direction.
		int winW, winH;
		glfwGetWindowSize(m_window, &winW, &winH);
		glm::vec2 cursorPos = m_userInput.GetCursorPosition();
		glm::vec2 scrCenter = glm::vec2( ((float)winW) * 0.5f, ((float)winH) * 0.5f);

		// cursor y pos is topleft need to get difference from scr height (scrCenter * 2).
		float yOffset = ((scrCenter[1] * 2.0f) - cursorPos[1]) - scrCenter[1]; 
		float xOffset = cursorPos[0] - scrCenter[0];

		float vectorLength = std::sqrtf(std::pow(xOffset, 2.0f) + std::pow(yOffset, 2.0f));
		if (vectorLength == 0.0f) vectorLength = 0.01f; // avoid divide by zero.
		glm::vec2 unitVector = glm::vec2(xOffset / vectorLength, yOffset / vectorLength);
		Bullet* bullet = new Bullet(m_player->GetCenter(), unitVector);
		m_bullets.push_back(bullet);
	}
}
void Game::RenderFrame()
{
	glm::vec4 clearColour(0.2f, 0.6f, 0.8f, 1.0f);
	m_renderer.ClearScreen(clearColour);

	m_renderer.StartBatch();
	for (Entity* entity : m_entities) entity->Render(m_renderer);
	for (Tile* tile : m_tiles) tile->Render(m_renderer);
	for (Bullet* bullet : m_bullets) bullet->Render(m_renderer);
	m_renderer.SubmitBatch();

	glfwSwapBuffers(m_window);
}
void Game::Update(float timeStep)
{
	for (Entity* entity : m_entities) entity->Update(timeStep);
	for (Bullet* bullet : m_bullets) bullet->Update(timeStep);
	EntityTileCollisions(timeStep);
	BulletTileCollisions();
}
bool Game::HasCollided(glm::vec4 rect1, glm::vec4 rect2)
{
	// vec4 -> x, y, width, height.
	if (rect1[0] < rect2[0] + rect2[2] &&
		rect1[0] + rect1[2] > rect2[0] &&
		rect1[1] < rect2[1] + rect2[3] &&
		rect1[1] + rect1[3] > rect2[1])
	{
		return true;
	}
	return false;
}
void Game::EntityTileCollisions(float timeStep)
{
	// Check/Resolve collisions.
	for (Entity* entity : m_entities)
	{
		float dx = entity->GetVelocityX();
		float dy = entity->GetVelocityY();

		float resolveStrength = 0.02f; // Increase this to speed up collision resolution.
		float xDir = 0.0f;
		float yDir = 0.0f;

		if (dx > 0) xDir = -1.0f;
		else if(dx < 0) xDir = 1.0f;
		if (dy > 0) yDir = -1.0f;
		else if (dy < 0) yDir = 1.0f;

		entity->Move(dx, 0.0f);
		for (Tile* tile : m_tiles)
		{
			while (HasCollided(entity->GetCollider(), tile->GetRect()))
			{
				entity->Move(xDir * resolveStrength, 0.0f);
			}
		}
		entity->Move(0.0f, dy);
		for (Tile* tile : m_tiles)
		{
			if (HasCollided(entity->GetCollider(), tile->GetRect()))
			{
				entity->SetVelocity(dx, 0.0f);
				if (dy < 0) entity->SetCanJump();
			}
			while (HasCollided(entity->GetCollider(), tile->GetRect()))
			{
				entity->Move(0.0f, yDir * resolveStrength);
			}
		}
	}
}
void Game::BulletTileCollisions()
{
	for (int i = 0; i < m_bullets.size(); i++)
	{
		bool collided = false;
		for (Tile* tile : m_tiles)
		{
			if (HasCollided(m_bullets[i]->GetRect(), tile->GetRect()))
			{
				collided = true;
				break;
			}
		}
		if (collided || m_bullets[i]->AliveTooLong())
		{
			m_bullets[i] = m_bullets.back();
			m_bullets.pop_back();
		}
	}
}
void Game::Reset()
{
	for (Entity* entity : m_entities) delete entity;
	for (Tile* tile : m_tiles) delete tile;
	for (Bullet* bullet : m_bullets) delete bullet;
	m_entities.clear();
	m_tiles.clear();
	m_bullets.clear();
}
