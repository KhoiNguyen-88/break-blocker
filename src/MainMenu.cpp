#include "Header.h"

void MainMenu::Init()
{
	m_startButton = new Texture();
	
	if (m_startButton->Load("start.png"))
	{
		SDL_Log("Load start button success");
	}
	else
		SDL_Log("Error while load start button");

	m_startButtonPosition.x = WIDTH / 2 - m_startButton->m_size.w / 2;
	m_startButtonPosition.y = HEIGHT / 2 - m_startButton->m_size.h / 2;
	/*
	m_exitButton = new Texture();
	
	if (m_exitButton->Load("quit.png"))
	{
		SDL_Log("Load start button success");
	}
	else
		SDL_Log("Error while load start button");

	m_exitButtonPosition.x = WIDTH / 2 - m_exitButton->m_size.w / 2  - 300;
	m_exitButtonPosition.y = HEIGHT / 2 - m_exitButton->m_size.h / 2 - 300;
	*/
}

void MainMenu::Update(Uint32 dt)
{
}

void MainMenu::Render()
{

	startBtn = m_startButton->m_size;
	startBtn.x = m_startButtonPosition.x;
	startBtn.y = m_startButtonPosition.y;
	startBtn.w = 600;
	startBtn.h = 600;

	SDL_RenderCopy(Shared::m_renderer, m_startButton->m_texture, NULL, &startBtn);


	exitBtn = m_startButton->m_size;
	exitBtn.x = m_exitButtonPosition.x;
	exitBtn.y = m_exitButtonPosition.y;
	exitBtn.w = 600;
	exitBtn.h = 600;

	SDL_RenderCopy(Shared::m_renderer, m_startButton->m_texture, NULL, &exitBtn);
}

void MainMenu::Destroy()
{
}

void MainMenu::HandleKeyEvent(int key, bool state)
{
	SDL_Log("Key: %c", key);
	if (key == 27)
	{
		SDL_Quit();
	}
}

void MainMenu::HandleMouseEvent(int x, int y, int button)
{
	if (x > startBtn.x
		&& y > startBtn.y
		&& x < startBtn.x + startBtn.w
		&& y < startBtn.y + startBtn.h)
	{
		printf("press game play \n");
		SCENE_MGR->ChangeScene(new GamePlay());
	}
	/*
	if (x > exitBtn.x
		&& y > exitBtn.y
		&& x < exitBtn.x + exitBtn.w
		&& y < exitBtn.y + exitBtn.h)
	{
		printf("press Game over \n");
		SCENE_MGR->ChangeScene(new GameOver());
	}
	*/
}
