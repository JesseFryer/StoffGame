#include "UserInput.h"

struct MouseState
{
    float cursorX = 0.0f;
    float cursorY = 0.0f;
    bool leftClick = false;
    bool rightClick = false;
};
static MouseState s_mouseState;

static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    s_mouseState.cursorX = (float)xpos;
    s_mouseState.cursorY = (float)ypos;
}
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS) s_mouseState.leftClick = true;
        else if (action == GLFW_RELEASE) s_mouseState.leftClick = false;
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS) s_mouseState.rightClick = true;
        else if (action == GLFW_RELEASE) s_mouseState.rightClick = false;
    }
}

UserInput::UserInput(GLFWwindow* window)
{
    m_window = window;
    m_keyStates[Key_W]   = false;
    m_keyStates[Key_A]   = false;
    m_keyStates[Key_S]   = false;
    m_keyStates[Key_D]   = false;
    m_keyStates[Key_SPC] = false;
    m_keyStates[Key_ESC] = false;

    glfwSetCursorPosCallback(m_window, CursorPositionCallback);
    glfwSetMouseButtonCallback(m_window, MouseButtonCallback);
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

bool UserInput::IsPressed(Key key)
{
    return m_keyStates[key];
}
bool UserInput::LeftClick()
{
    return s_mouseState.leftClick;
}
bool UserInput::RightClick()
{
    return s_mouseState.rightClick;
}
glm::vec2 UserInput::GetCursorPosition()
{
    return glm::vec2(s_mouseState.cursorX, s_mouseState.cursorY);
}
