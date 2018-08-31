#pragma once

class Application
{
private:
	SDL_Window * m_window;
	SDL_Renderer* m_renderer;

	// khai bao texture
	Texture* m_ball;
	Texture* m_background;

	Sound* m_sound;


	SDL_Event mainEvent;

	SDL_Rect sourceRect;
	SDL_Rect dst;
	SDL_Rect bg;

	SDL_Rect  gRacket; 
	SDL_Point gBrickDirection;

	SDL_Rect gTarget[NUMBER_OF_TARGET];

	//khai bao su kien
	bool isRunning = true;

public:
	
	void Init();

	void SetPoint();

	void CheckgBrickHitRacket();

	void Brick();

	void CheckGameOver();

	void Target();

	void EventDriven();

	void Update();

	void Render();

	void Destroy();

	void Run();

	
};

