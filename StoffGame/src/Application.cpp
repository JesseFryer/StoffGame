#include "renderer\Renderer.h"
#include "UserInput.h"

#include <iostream>

// Globals.
float MOUSE_SCROLL = 0.0f;
float MOUSE_SCROLL_SENSITIVITY = 0.2f;
float CAMERA_SPEED = 2.0f;

void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);

int main()
{
	// Setup.
	Renderer2D renderer;
	GLFWwindow* window = renderer.GetWindow();
	UserInput userInput(window);

	// Callbacks.
	glfwSetScrollCallback(window, ScrollCallback);

	while (!glfwWindowShouldClose(window))
	{
		userInput.UpdateInputs();

		// Camera movement test with input class.
		if (userInput.IsPressed(Key_ESC)) glfwSetWindowShouldClose(window, true);
		if (userInput.IsPressed(Key_W)) renderer.MoveCamera(0.0f, CAMERA_SPEED);
		if (userInput.IsPressed(Key_A)) renderer.MoveCamera(-CAMERA_SPEED, 0.0f);
		if (userInput.IsPressed(Key_S)) renderer.MoveCamera(0.0f, -CAMERA_SPEED);
		if (userInput.IsPressed(Key_D)) renderer.MoveCamera(CAMERA_SPEED, 0.0f);
		renderer.ZoomCamera(MOUSE_SCROLL);
		MOUSE_SCROLL *= 0.9f; // Slowly decreases scroll value for smooth zooming in/out.

		// ------------------------ Render here ------------------------
		glm::vec4 clearColour(0.2f, 0.6f, 0.8f, 1.0f);
		renderer.ClearScreen(clearColour);

		renderer.StartBatch();

		renderer.AddQuad(glm::vec2(-50.0f, -50.0f), glm::vec2(100.0f), glm::vec4(1.0f)); // White 100p x 100p square.

		renderer.SubmitBatch();
		// -------------------------------------------------------------

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}

void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	MOUSE_SCROLL = ((float) yOffset) * MOUSE_SCROLL_SENSITIVITY;
}