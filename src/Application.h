#pragma once

class Application
{
private:
	SDL_Window*		m_window;
	//SDL_Renderer*	m_renderer;

	//bool			m_isRunning;

public:
	Application();

	void			Init();

	void			Destroy();
	void			QueryEvents();

	void			Run(int fps);
};

