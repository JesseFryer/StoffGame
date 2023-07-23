#pragma once

#include "Game.h"
#include <iostream>

struct Globals
{
	float MOUSE_SCROLL = 0.0f;
	const float MOUSE_SCROLL_SENSITIVITY = 0.1f;

	const float CAMERA_SPEED = 2.0f;

	const glm::vec2 SPAWN_POINT = glm::vec2(600.0f, 1000.0f);

	const unsigned int MAX_PARTICLES = 1000;
	unsigned int PARTICLE_COUNT = 0;

	const unsigned int MAX_BULLETS = 20;
	unsigned int BULLET_COUNT = 0;
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
	UseMap("map1");

	// Initialise recycleable instances.
	for (size_t i = 0; i < globals.MAX_PARTICLES; i++)
	{
		m_particles[i] = Particle();
	}
	for (size_t i = 0; i < globals.MAX_BULLETS; i++)
	{
		m_bullets[i] = Bullet();
	}

	// Setup animations.
	m_player = new Player(&m_userInput);
	m_player->SetTexID(m_textureIDs["player"]);
	std::vector<unsigned int> playerIdleFrames = { 0, 1, 2, 3, 4, 5 };
	m_player->AddAnimation(IDLE, m_spriteSheets["player"]->GetAnimation(playerIdleFrames, false), 8.0f);
	m_player->SetCurrentAnimation(IDLE);
	m_player->SetSize(glm::vec2(20.0f, 32.0f));
	Enemy::SetPlayerPointer(m_player);

	NewGame();
}
Game::~Game()
{
	delete m_player;
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
			for (int i = 0; i < 2; i++)
			{
				Enemy* enemy = new Enemy(glm::vec2(i * 450.0f, 1000.0f));
				enemy->SetCurrentAnimation(NONE);
				enemy->SetTexID(m_textureIDs["enemy"]);
				m_enemies.push_back(enemy);
			}
			logFpsCounter = 0;
			std::cout << 1.0 / timeStep << "\n";
		}

		Update(timeStep);
		m_renderer.SetCameraPosition(m_player->GetCenter());
		m_renderer.ZoomCamera(globals.MOUSE_SCROLL);
		globals.MOUSE_SCROLL *= 0.95f; // Slowly decreases scroll value for smooth zooming in/out.
		RenderFrame();

		if (m_player->IsDead())
		{
			m_menu.Run();
			if (m_menu.NewGame()) NewGame();
			if (m_menu.Quit()) m_running = false;
			lastTime = glfwGetTime();
		}
	}
	glfwTerminate();
}

void Game::NewGame()
{
	m_enemies.clear();
	m_player->SetPosition(globals.SPAWN_POINT);
	m_player->ResetHealth();
}
void Game::LoadMap(const char* filePath, std::string mapName)
{
	m_maps[mapName] = Map(filePath);
}
void Game::UseMap(std::string mapName)
{
	const float TILE_SIZE = 16.0f;

	// Clear old map.
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
				Tile tile = Tile(glm::vec2(xPos, yPos), type);
				tile.SetTexID(m_textureIDs["tiles"]);
				tile.SetTexCoords(m_tileTexCoords[type]);
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
	m_textureIDs["enemy"] = m_renderer.LoadTexture("res/sprites/enemy.png");
	m_spriteSheets["enemy"] = new SpriteSheet(16, 8, 16, 8);
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

		m_bullets[m_bulletsIndex].SetPosition(m_player->GetCenter());
		m_bullets[m_bulletsIndex].SetUnitVector(unitVector);
		m_bullets[m_bulletsIndex].SetActive();
		m_bulletsIndex++;
		if (m_bulletsIndex > globals.MAX_BULLETS)
		{
			m_bulletsIndex = 0;
		}
	}
}
void Game::RenderFrame()
{
	glm::vec4 clearColour(0.2f, 0.6f, 0.8f, 1.0f);
	m_renderer.ClearScreen(clearColour);

	m_renderer.StartBatch();

	for (Tile tile : m_tiles)
	{
		tile.Render(m_renderer);
	}
	m_player->Render(m_renderer);
	for (Enemy* entity : m_enemies) 
	{
		entity->Render(m_renderer);
	}
	for (size_t i = 0; i < globals.MAX_BULLETS; i++)
	{
		if (m_bullets[i].IsActive()) m_bullets[i].Render(m_renderer);
	}
	for (size_t i = 0; i < globals.MAX_PARTICLES; i++)
	{
		if (m_particles[i].IsAlive()) m_particles[i].Render(m_renderer);
	}

	m_renderer.SubmitBatch();

	glfwSwapBuffers(m_window);
}
void Game::Update(float timeStep)
{
	m_player->Update(timeStep);
	for (Enemy* enemy : m_enemies) enemy->Update(timeStep);
	for (size_t i = 0; i < globals.MAX_BULLETS; i++)
	{
		if (m_bullets[i].IsActive()) m_bullets[i].Update(timeStep);
	}
	for (size_t i = 0; i < globals.MAX_PARTICLES; i++)
	{
		if (m_particles[i].IsAlive()) m_particles[i].Update(timeStep);
	}
	PlayerTileCollisions(timeStep);
	EntityTileCollisions(timeStep);
	BulletTileCollisions(timeStep);
	BulletEnemyCollisions(timeStep);
	ParticleTileCollisions(timeStep);
	PlayerEnemyCollisions();
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
	for (Enemy* entity : m_enemies)
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

		entity->Move(dx * timeStep, 0.0f);
		for (Tile tile : m_tiles)
		{
			while (HasCollided(entity->GetCollider(), tile.GetRect()))
			{
				entity->Move(xDir * resolveStrength, 0.0f);
			}
		}
		entity->Move(0.0f, dy * timeStep);
		for (Tile tile : m_tiles)
		{
			if (HasCollided(entity->GetCollider(), tile.GetRect()))
			{
				entity->SetVelocity(dx, 0.0f);
				if (dy < 0) entity->SetCanJump();
			}
			while (HasCollided(entity->GetCollider(), tile.GetRect()))
			{
				entity->Move(0.0f, yDir * resolveStrength);
			}
		}
	}
}
void Game::BulletTileCollisions(float timeStep)
{
	for (size_t i = 0; i < globals.MAX_BULLETS; i++)
	{
		if (m_bullets[i].IsActive())
		{
			for (Tile tile : m_tiles)
			{
				if (HasCollided(m_bullets[i].GetRect(), tile.GetRect()))
				{
					m_bullets[i].SetInactive();
					break;
				}
			}
		}
	}
}
void Game::ParticleTileCollisions(float timeStep)
{
	for (size_t i = 0; i < globals.MAX_PARTICLES; i++)
	{
		if (m_particles[i].IsAlive())
		{
			float dx = m_particles[i].GetVelocityX();
			float dy = m_particles[i].GetVelocityY();

			float resolveStrength = 0.2f; // Increase this to speed up collision resolution.
			float xDir = 0.0f;
			float yDir = 0.0f;

			if (dx > 0) xDir = -1.0f;
			else if (dx < 0) xDir = 1.0f;
			if (dy > 0) yDir = -1.0f;
			else if (dy < 0) yDir = 1.0f;

			m_particles[i].Move(dx * timeStep, 0.0f);
			for (Tile tile : m_tiles)
			{
				if (HasCollided(m_particles[i].GetRect(), tile.GetRect()))
				{
					dx = 0.0f;
					float resolve = xDir * resolveStrength;
					while (HasCollided(m_particles[i].GetRect(), tile.GetRect()))
					{
						m_particles[i].Move(resolve, 0.0f);
					}
					break;
				}
			}
			m_particles[i].Move(0.0f, dy * timeStep);
			for (Tile tile : m_tiles)
			{
				if (HasCollided(m_particles[i].GetRect(), tile.GetRect()))
				{
					dy = 0.0f;
					float resolve = yDir * resolveStrength;
					while (HasCollided(m_particles[i].GetRect(), tile.GetRect()))
					{
						m_particles[i].Move(0.0f, resolve);
					}
					break;
				}
			}
			m_particles[i].SetVelocity(dx, dy);
		}

	}
}
void Game::BulletEnemyCollisions(float timeStep)
{
	const static float knockBackStrength = 100.0f;
	for (size_t i = 0; i  < globals.MAX_BULLETS; i++)
	{
		if (m_bullets[i].IsActive())
		{
			bool collided = false;
			for (int j = 0; j < m_enemies.size(); j++)
			{
				Enemy* enemy = m_enemies[j];
				if (HasCollided(m_bullets[i].GetRect(), enemy->GetRect()))
				{
					collided = true;
					float knockBack = m_bullets[i].GetXDirection() * knockBackStrength;
					enemy->SetVelocity(knockBack, 50.0f);
					enemy->Damage(10.0f);
					if (enemy->IsDead())
					{
						GenerateParticles(enemy->GetCenter(), 150);
						m_enemies[j] = m_enemies.back();
						m_enemies.pop_back();
						m_player->Damage(-1.0f);
					}
					break;
				}
			}
		}
	}
}
void Game::PlayerTileCollisions(float timeStep)
{
	float dx = m_player->GetVelocityX();
	float dy = m_player->GetVelocityY();

	float resolveStrength = 0.02f; // Increase this to speed up collision resolution.
	float xDir = 0.0f;
	float yDir = 0.0f;

	if (dx > 0) xDir = -1.0f;
	else if (dx < 0) xDir = 1.0f;
	if (dy > 0) yDir = -1.0f;
	else if (dy < 0) yDir = 1.0f;

	m_player->Move(dx * timeStep, 0.0f);
	for (Tile tile : m_tiles)
	{
		while (HasCollided(m_player->GetCollider(), tile.GetRect()))
		{
			m_player->Move(xDir * resolveStrength, 0.0f);
		}
	}
	m_player->Move(0.0f, dy * timeStep);
	for (Tile tile : m_tiles)
	{
		if (HasCollided(m_player->GetCollider(), tile.GetRect()))
		{
			m_player->SetVelocity(dx, 0.0f);
			if (dy < 0) m_player->SetCanJump();
			m_player->StopKnockBack();
		}
		while (HasCollided(m_player->GetCollider(), tile.GetRect()))
		{
			m_player->Move(0.0f, yDir * resolveStrength);
		}
	}
}
void Game::PlayerEnemyCollisions()
{
	glm::vec4 playerCollider = m_player->GetCollider();
	if (!m_player->IsImmune())
	{
		for (Enemy* enemy : m_enemies)
		{
			if (HasCollided(playerCollider, enemy->GetRect()))
			{
				float knockback;
				if (enemy->GetCenter()[0] > m_player->GetCenter()[0])
				{
					knockback = -1.0f;
				}
				else
				{
					knockback = 1.0f;
				}
				m_player->KnockBack(knockback);
				m_player->SetVelocity(m_player->GetVelocityX(), 300.0f);
				m_player->Damage(10.0f);
				break;
			}
		}
	}

}
void Game::GenerateParticles(glm::vec2 position, unsigned int numOfParticles)
{
	const static float maxSize = 2.5f;
	const static float totalAngle = 3.14f;
	const static float maxSpeed = 270.0f;

	for (int i = 0; i < numOfParticles; i++)
	{
		float randomFloat1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float randomFloat2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float randomFloat3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float angle = randomFloat1 * totalAngle;
		glm::vec2 size = glm::vec2(maxSize * randomFloat2);
		float speed = maxSpeed * randomFloat3;
	
		m_particles[m_particlesIndex].Reset();
		m_particles[m_particlesIndex].SetPosition(position);
		m_particles[m_particlesIndex].SetVelocity(speed * cos(angle), speed * sin(angle));
		m_particles[m_particlesIndex].SetSize(size);
		m_particlesIndex++;
		
		if (m_particlesIndex == globals.MAX_PARTICLES)
		{
			m_particlesIndex = 0;
		}
	}
}