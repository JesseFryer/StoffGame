#include "MainMenu.h"

MainMenu::MainMenu(Renderer2D* renderer, UserInput* input)
{
    m_renderer = renderer;
    m_userInput = input;
    m_window = m_renderer->GetWindow();
}

void MainMenu::Run()
{
    m_running = true;
    m_newGame = false;
    m_quit = false;
    while (m_running)
    {
        Update();
        Render();
    }
}

bool MainMenu::NewGame()
{
    return m_newGame;
}

bool MainMenu::Quit()
{
    return m_quit;
}

void MainMenu::Render()
{
    glm::vec4 colour = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
    m_renderer->ClearScreen(colour);
    glfwSwapBuffers(m_window);
}

void MainMenu::Update()
{
    glfwPollEvents();
    m_userInput->UpdateInputs();
    if (m_userInput->IsPressed(Key_SPC))
    {
        m_newGame = true;
        m_running = false;
        m_quit = false;
    }
    if (m_userInput->IsPressed(Key_ESC))
    {
        m_newGame = false;
        m_running = false;
        m_quit = true;
    }
}
