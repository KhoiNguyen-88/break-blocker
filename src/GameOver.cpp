#include "Header.h"

void GameOver::Init()
{
	m_GameOverTitle = new Texture();

	if (m_GameOverTitle->Load("images.png"))
	{
		SDL_Log("Load start button success");
	}
	else
		SDL_Log("Error while load start button");

	m_GameOverTitlePosition.x = WIDTH / 2 - m_GameOverTitle->m_size.w / 2;
	m_GameOverTitlePosition.y = HEIGHT / 2 - m_GameOverTitle->m_size.h / 2;


	m_PlayAgainButton = new Texture();

	if (m_PlayAgainButton->Load("images.png"))
	{
		SDL_Log("Load start button success");
	}
	else
		SDL_Log("Error while load start button");

	m_PlayAgainPosition.x = WIDTH / 2 - m_PlayAgainButton->m_size.w / 2;
	m_PlayAgainPosition.y = HEIGHT / 2 - m_PlayAgainButton->m_size.h / 2;


}

void GameOver::Update(Uint32 dt)
{
}

void GameOver::Render()
{
	GameOverTitle = m_GameOverTitle->m_size;
	GameOverTitle.x = m_GameOverTitlePosition.x;
	GameOverTitle.y = m_GameOverTitlePosition.y;
	GameOverTitle.w = 600;
	GameOverTitle.h = 600;

	SDL_RenderCopy(Shared::m_renderer, m_GameOverTitle->m_texture, NULL, &GameOverTitle);


	PlayAgain = m_PlayAgainButton->m_size;
	PlayAgain.x = m_PlayAgainPosition.x;
	PlayAgain.y = m_PlayAgainPosition.y;
	PlayAgain.w = 600;
	PlayAgain.h = 600;

	SDL_RenderCopy(Shared::m_renderer, m_PlayAgainButton->m_texture, NULL, &PlayAgain);
}

void GameOver::Destroy()
{
}

void GameOver::HandleKeyEvent(int key, bool state)
{

}

void GameOver::HandleMouseEvent(int x, int y, int button)
{
	if (x > PlayAgain.x
		&& y > PlayAgain.y
		&& x < PlayAgain.x + PlayAgain.w
		&& y < PlayAgain.y + PlayAgain.h)
	{
		printf("press Game over \n");
		SCENE_MGR->ChangeScene(new GameOver());
	}

}
