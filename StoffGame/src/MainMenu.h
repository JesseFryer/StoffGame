#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "renderer\Renderer.h"
#include "utils\UserInput.h"

class MainMenu
{
public:
	MainMenu(Renderer2D* renderer, UserInput* input);
	void Run();
	bool NewGame();
	bool Quit();

private:
	void Render();
	void Update();

private:
	bool m_newGame = false;
	bool m_quit = false;
	bool m_running = false;
	Renderer2D* m_renderer;
	GLFWwindow* m_window;
	UserInput* m_userInput;
};

#endif 

