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
}

void MainMenu::Update(Uint32 dt)
{
}

void MainMenu::Render()
{
	SDL_Rect startBtn;
	startBtn = m_startButton->m_size;
	startBtn.x = m_startButtonPosition.x;
	startBtn.y = m_startButtonPosition.y;

	SDL_RenderCopy(Shared::m_renderer, m_startButton->m_texture, NULL, &startBtn);
}

void MainMenu::Destroy()
{
}

void MainMenu::HandleKeyEvent(int key, bool state)
{
	SDL_Log("Key: %c", key);
}

void MainMenu::HandleMouseEvent(int x, int y, int button)
{
}
