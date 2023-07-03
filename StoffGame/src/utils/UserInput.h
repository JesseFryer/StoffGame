#pragma once

#include "GLFW\glfw3.h"
#include <unordered_map>

enum Key
{
	Key_W, Key_A, Key_S, Key_D,
	Key_SPC, Key_ESC
};

class UserInput
{
public:
	UserInput(GLFWwindow* window);
	bool IsPressed(Key key);
	void UpdateInputs();

private:
	std::unordered_map<Key, bool> m_keyStates;
	GLFWwindow* m_window;
};