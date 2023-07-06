#pragma once

#include "Game.h"
#include <iostream>

struct Globals
{
	float MOUSE_SCROLL = 0.0f;
	const float MOUSE_SCROLL_SENSITIVITY = 0.1f;
	const float CAMERA_SPEED = 2.0f;
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
}
Game::~Game()
{
	for (Sprite* sprite : m_sprites) delete sprite;
	for (Tile* tile : m_tiles) delete tile;
	for (auto& pair : m_spriteSheets) delete pair.second;
}

void Game::Run()
{
	NewGame();
	float lastTime = 0.0f;
	while (m_running)
	{
		float currentTime = glfwGetTime();
		float timeStep = currentTime - lastTime;
		lastTime = currentTime;
		HandleInput();
		m_renderer.SetCameraPosition(m_player->GetPosition());
		m_renderer.ZoomCamera(globals.MOUSE_SCROLL);
		globals.MOUSE_SCROLL *= 0.95f; // Slowly decreases scroll value for smooth zooming in/out.
		Update(timeStep);
		RenderFrame();
	}
	glfwTerminate();
}

void Game::NewGame()
{
	m_sprites.clear();
	m_entities.clear();

	Sprite* whiteSquare = new Sprite(glm::vec2(-50.0f));
	Entity* coin = new Entity();
	m_player = new Player(&m_userInput);

	m_sprites.push_back(whiteSquare);
	m_sprites.push_back(coin);
	m_sprites.push_back(m_player);

	m_entities.push_back(coin);
	
	coin->SetTexID(m_textureIDs["coin"]);
	std::vector<unsigned int> coinSpinFrames = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	coin->AddAnimation(IDLE, m_spriteSheets["coin"]->GetAnimation(coinSpinFrames, false), 52.0f);
	coin->SetCurrentAnimation(IDLE);
	coin->SetGravity(0.0f);

	m_player->SetTexID(m_textureIDs["player"]);
	std::vector<unsigned int> playerIdleFrames = { 0, 1, 2, 3, 4, 5 };
	m_player->AddAnimation(IDLE, m_spriteSheets["player"]->GetAnimation(playerIdleFrames, false), 8.0f);
	m_player->SetCurrentAnimation(IDLE);
	m_player->SetSize(glm::vec2(20.0f, 32.0f));

	UseMap("map1");
}
void Game::LoadMap(const char* filePath, std::string mapName)
{
	m_maps[mapName] = Map(filePath);
}
void Game::UseMap(std::string mapName)
{
	float TILE_SIZE = 16.0f;

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
			Tile* tile = new Tile(glm::vec2(xPos * TILE_SIZE, yPos * TILE_SIZE), type);
			m_tiles.push_back(tile);
			xPos++;
		}
		yPos++;
	}
}
void Game::LoadTextures()
{
	m_textureIDs["player"] = m_renderer.LoadTexture("res/sprites/PlayerSpriteSheet.png");
	m_spriteSheets["player"] = new SpriteSheet(200, 320, 20, 32);
	m_textureIDs["coin"] = m_renderer.LoadTexture("res/sprites/coin.png");
	m_spriteSheets["coin"] = new SpriteSheet(208, 16, 16, 16);

}
void Game::HandleInput()
{
	glfwPollEvents();
	m_userInput.UpdateInputs();
	if (m_userInput.IsPressed(Key_ESC)) m_running = false;
}
void Game::RenderFrame()
{
	glm::vec4 clearColour(0.2f, 0.6f, 0.8f, 1.0f);
	m_renderer.ClearScreen(clearColour);
	m_renderer.StartBatch();
	for (Sprite* sprite : m_sprites) sprite->Render(m_renderer);
	for (Tile* tile : m_tiles) tile->Render(m_renderer);
	m_renderer.SubmitBatch();
	glfwSwapBuffers(m_window);
}
void Game::Update(float timeStep)
{
	for (Entity* entity : m_entities) entity->Update(timeStep);
	m_player->Update(timeStep);
}