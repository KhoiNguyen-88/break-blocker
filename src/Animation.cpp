#include "Header.h"


void Animation::Play() 
{
	m_isPlaying = true;
	m_currentFrame = 0;
	m_countingTime = 0;
}

void Animation::Stop()
{
	m_isPlaying = false;
}

void Animation::SetFPS(int fps)
{
	m_frameTime = 1000 / fps;
}

void Animation::Update(float dt)
{
	if (m_isPlaying && m_countingTime > m_frameTime) {
		m_currentFrame = (m_currentFrame + 1) % m_totalFrame;
		m_countingTime = 0;
	}
	else {
		m_countingTime += dt;
	}
}

void Animation::Render(int posX, int posY)
{
	Sprite::renderFrame(m_currentFrame, posX, posY);
}

Animation::Animation(const char * path, const char * config_path) : Sprite(path, config_path)
{
}
