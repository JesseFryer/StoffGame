#pragma once

#include "GLAD/glad.h"
#include "GLFW/glfw3.h"
#include "GLM/glm.hpp"

class Renderer2D
{

public:
	Renderer2D();

	static void StartBatch();
	static void SubmitBatch();
	static void AddQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& colour);
	static void AddQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& texCoords, float texIndex);
	static void ClearScreen(glm::vec4 clearColour);
	static float LoadTexture(const char* filePath);

	static GLFWwindow* GetWindow();
	static void SetCameraPosition(glm::vec2& position);
	static void MoveCamera(float dx, float dy);
	static void ZoomCamera(float zoom);

private:
	static void Init();
	static void InitWindow();
	static void InitBuffers();
	static void Flush();
	static void AddQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& texCoords, const glm::vec4& colour, float texIndex);
};