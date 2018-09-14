#pragma once

class Animation : public Sprite {
	int m_currentFrame;
	bool m_isPlaying;

	Uint32 m_countingTime;
	Uint32 m_frameTime;

public:
	void Play();
	void Stop();
	void SetFPS(int fps);

	void Update(float dt);
	void Render(int posX, int posY);

	Animation(const char* path, const char* config_path);
	~Animation();
};