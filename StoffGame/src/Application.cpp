#include "renderer/Renderer.h"
#include "utils/UserInput.h"
#include "utils/Globals.h"

#include <iostream>

static Globals globals;

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
	globals.MOUSE_SCROLL = ((float) yOffset) * globals.MOUSE_SCROLL_SENSITIVITY;
}