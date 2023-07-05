#pragma once

#include "Game.h"
#include <iostream>
#include <thread>

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
}
Game::~Game()
{
	for (Sprite* sprite : m_sprites) delete sprite;
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
		Update(timeStep);
		RenderFrame();
		glfwPollEvents();
	}
	glfwTerminate();
}

void Game::NewGame()
{
	m_sprites.clear();
	m_animatedSprites.clear();

	// Load Game. Test with both Animated and base Sprite.
	Sprite* sprite1 = new Sprite(glm::vec2(-50.0f));
	AnimatedSprite* sprite2 = new AnimatedSprite();
	m_sprites.push_back(sprite1);
	m_sprites.push_back(sprite2);
	m_animatedSprites.push_back(sprite2);

	sprite2->SetTexID(m_textureIDs["coin"]);
	std::vector<unsigned int> indices = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
	};
	sprite2->AddAnimation(IDLE, m_spriteSheets["coin"]->GetAnimation(indices, false), 52.0f);
	sprite2->SetCurrentAnimation(IDLE);
}
void Game::LoadTextures()
{
	m_textureIDs["coin"] = m_renderer.LoadTexture("res/sprites/coin.png");
	m_spriteSheets["coin"] = new SpriteSheet(208, 16, 16, 16);
}
void Game::HandleInput()
{
	m_userInput.UpdateInputs();
	// Camera movement test with input class.
	if (m_userInput.IsPressed(Key_ESC)) m_running = false;
	if (m_userInput.IsPressed(Key_W)) m_renderer.MoveCamera(0.0f, globals.CAMERA_SPEED);
	if (m_userInput.IsPressed(Key_A)) m_renderer.MoveCamera(-globals.CAMERA_SPEED, 0.0f);
	if (m_userInput.IsPressed(Key_S)) m_renderer.MoveCamera(0.0f, -globals.CAMERA_SPEED);
	if (m_userInput.IsPressed(Key_D)) m_renderer.MoveCamera(globals.CAMERA_SPEED, 0.0f);
	m_renderer.ZoomCamera(globals.MOUSE_SCROLL);
	globals.MOUSE_SCROLL *= 0.95f; // Slowly decreases scroll value for smooth zooming in/out.
}
void Game::RenderFrame()
{
	glm::vec4 clearColour(0.2f, 0.6f, 0.8f, 1.0f);
	m_renderer.ClearScreen(clearColour);
	m_renderer.StartBatch();
	for (Sprite* sprite : m_sprites) sprite->Render(m_renderer);
	m_renderer.SubmitBatch();
	glfwSwapBuffers(m_window);
}
void Game::Update(float timeStep)
{
	for (AnimatedSprite* sprite : m_animatedSprites) sprite->Update(timeStep);
}