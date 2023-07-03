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
	glfwSetScrollCallback(window, ScrollCallback);
}

void Game::Run()
{
	NewGame();
	while (!glfwWindowShouldClose(window))
	{
		userInput.UpdateInputs();

		// Camera movement test with input class.
		if (userInput.IsPressed(Key_ESC)) glfwSetWindowShouldClose(window, true);
		if (userInput.IsPressed(Key_W)) renderer.MoveCamera(0.0f, globals.CAMERA_SPEED);
		if (userInput.IsPressed(Key_A)) renderer.MoveCamera(-globals.CAMERA_SPEED, 0.0f);
		if (userInput.IsPressed(Key_S)) renderer.MoveCamera(0.0f, -globals.CAMERA_SPEED);
		if (userInput.IsPressed(Key_D)) renderer.MoveCamera(globals.CAMERA_SPEED, 0.0f);
		renderer.ZoomCamera(globals.MOUSE_SCROLL);
		globals.MOUSE_SCROLL *= 0.95f; // Slowly decreases scroll value for smooth zooming in/out.

		// ------------------------ Render here ------------------------
		glm::vec4 clearColour(0.2f, 0.6f, 0.8f, 1.0f);
		renderer.ClearScreen(clearColour);

		renderer.StartBatch();

		for (Sprite* sprite : m_sprites) sprite->Render(renderer);

		renderer.SubmitBatch();
		// -------------------------------------------------------------

		glfwSwapBuffers(window);
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
}
