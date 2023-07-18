#pragma once

#include "GLFW\glfw3.h"
#include "GLM\glm.hpp"
#include <unordered_map>

enum Key
{
	Key_W, Key_A, Key_S, Key_D,
	Key_SPC, Key_ESC
};

enum MouseButton
{
	LEFT_CLK, RIGHT_CLK
};

class UserInput
{
public:
	UserInput(GLFWwindow* window);
	bool IsPressed(Key key);
	void UpdateInputs();
	bool LeftClick();
	bool RightClick();
	glm::vec2 GetCursorPosition();

private:
	std::unordered_map<Key, bool> m_keyStates;
	std::unordered_map<MouseButton, bool> m_mouseStates;
	GLFWwindow* m_window;
};