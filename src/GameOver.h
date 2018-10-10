#pragma once

class GameOver : public Scene {
	Texture*	m_GameOverTitle;
	SDL_Point	m_GameOverTitlePosition;

	Texture*	m_PlayAgainButton;
	SDL_Point	m_PlayAgainPosition;

	SDL_Rect	GameOverTitle;
	SDL_Rect	PlayAgain;

public:
	void Init() override;
	void Update(Uint32 dt) override;
	void Render() override;
	void Destroy() override;

	void HandleKeyEvent(int key, bool state) override;
	void HandleMouseEvent(int x, int y, int button) override;
};