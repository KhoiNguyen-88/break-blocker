#pragma once

class MainMenu : public Scene 
{
	Texture*	m_startButton;
	SDL_Point	m_startButtonPosition;

public:
	void Init() override;
	void Update(Uint32 dt) override;
	void Render() override;
	void Destroy() override;

	void HandleKeyEvent(int key, bool state) override;
	void HandleMouseEvent(int x, int y, int button) override;
};