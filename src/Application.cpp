#include "Header.h"

Application::Application() : m_window(NULL), m_renderer(NULL), m_currentScene(NULL)
{
}

void Application::Init() {
	// Init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_Log("Unable to initialize SDL %s\n", SDL_GetError());
	}

	m_window = SDL_CreateWindow("Stdio.vn - SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (m_window == NULL)
	{
		SDL_Log("Could not create window %s", SDL_GetError());
	}

	// Init SDL Image
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	if ((IMG_Init(flags) & flags) != flags)
	{
		SDL_Log("IMG_Init: Failed to init required jpg and png support!\n");
		SDL_Log("IMG_Init: %s\n", IMG_GetError());
	}

	//Init SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		SDL_Log("%s", Mix_GetError());
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (m_renderer == NULL)
	{
		SDL_Log("Unable to init renderer. Error: %s", SDL_GetError());
	}

	Shared::m_renderer = m_renderer;
}

void Application::Destroy()
{
	//Destroy Audio
	Mix_CloseAudio();
	
	//Destroy a window.
	SDL_DestroyWindow(m_window);

	//Destroy a renderer
	SDL_DestroyRenderer(m_renderer);

	//cleans up all initialized subsystems
	SDL_Quit();
}

void Application::QueryEvents()
{
	SDL_Event mainEvent;

	while (SDL_PollEvent(&mainEvent))
	{
		switch (mainEvent.type)
		{
			//User - requested quit
			case SDL_QUIT:
			{
				m_isRunning = false;
				break;
			}
			case SDL_KEYDOWN:
			{
				m_currentScene->HandleKeyEvent(mainEvent.key.keysym.sym, true);
				break;
			}
			default:
			{
			}
		}
	}
}

void Application::Run(int fps) {
	if (m_currentScene == NULL)
	{
		SDL_Log("# Error: No start scene");
		Destroy();
		
		return;
	}

	Uint32 frameTime = 1000.0f / fps;
	Uint32 startTime = 0, endTime = 0, deltaTime = frameTime;

	m_isRunning = true;

	while (m_isRunning)
	{
		startTime = SDL_GetTicks();
		
		QueryEvents();

		// *****
		m_currentScene->Update(frameTime);
		// *****
		
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(m_renderer);

		// *****
		m_currentScene->Render();
		// *****

		SDL_RenderPresent(m_renderer);

		endTime = SDL_GetTicks();
		deltaTime = endTime - startTime;

		if (deltaTime < frameTime)
		{
			SDL_Delay(frameTime - deltaTime);
			deltaTime = frameTime;
		}
	}
	Destroy();
}

void Application::SetStartScene(Scene * scene)
{
	m_currentScene = scene;
	m_currentScene->Init();
}

