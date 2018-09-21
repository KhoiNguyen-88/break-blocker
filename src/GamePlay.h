#pragma once

class GamePlay : public Scene {
	// khai bao texture
	Texture* m_ball;
	Texture* m_background;

	Texture* m_SpriteFireBall;

	Sprite* m_BlockBreaker;
	// khai bao sound
	Sound* m_sound;

	// khai bao music
	Music* m_music;

	SDL_Rect sourceRect;
	SDL_Rect dst;
	SDL_Rect bg;

	SDL_Rect  gRacket;
	SDL_Point gBrickDirection;

	SDL_Rect gTarget[NUMBER_OF_TARGET];

	int currentFrameIndex;

	Animation* m_anim;
public:
	SDL_Rect m_button;

	void init();
	void update();
	void render();
	void destroy();
	GamePlay();

private:
	void SetPoint();

	void CheckgBrickHitRacket();

	void Brick();

	void CheckGameOver();

	void Target();

	void RenderFrame(int frameIndex, int x, int y);
};