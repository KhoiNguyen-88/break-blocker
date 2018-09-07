#pragma once

class Sprite{
public:
	SDL_Texture * m_texture;
	SDL_Rect	m_size;
	SDL_Rect    frames[16];
	int currentFrameIndex = 0;

	Sprite(const char* NameSprite, const char* SpriteConfig);
	void renderFrame(int index, int posX, int posY);
};