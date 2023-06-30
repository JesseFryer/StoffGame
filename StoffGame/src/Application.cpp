#include "renderer\Renderer.h"

int main()
{
	Renderer2D renderer;
	GLFWwindow* window = renderer.GetWindow();

	while (!glfwWindowShouldClose(window))
	{
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