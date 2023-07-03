#include "UserInput.h"

UserInput::UserInput(GLFWwindow* window)
{
    m_window = window;
    m_keyStates[Key_W]   = false;
    m_keyStates[Key_A]   = false;
    m_keyStates[Key_S]   = false;
    m_keyStates[Key_D]   = false;
    m_keyStates[Key_SPC] = false;
    m_keyStates[Key_ESC] = false;
}
bool UserInput::IsPressed(Key key)
{
    return m_keyStates[key];
}
void UserInput::UpdateInputs()
{ 
    glfwGetKey(m_window, GLFW_KEY_W)      ? m_keyStates[Key_W]   = true : m_keyStates[Key_W]   = false;
    glfwGetKey(m_window, GLFW_KEY_A)      ? m_keyStates[Key_A]   = true : m_keyStates[Key_A]   = false;
    glfwGetKey(m_window, GLFW_KEY_S)      ? m_keyStates[Key_S]   = true : m_keyStates[Key_S]   = false;
    glfwGetKey(m_window, GLFW_KEY_D)      ? m_keyStates[Key_D]   = true : m_keyStates[Key_D]   = false;
    glfwGetKey(m_window, GLFW_KEY_SPACE)  ? m_keyStates[Key_SPC] = true : m_keyStates[Key_SPC] = false;
    glfwGetKey(m_window, GLFW_KEY_ESCAPE) ? m_keyStates[Key_ESC] = true : m_keyStates[Key_ESC] = false;
}