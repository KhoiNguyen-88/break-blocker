#pragma once

class Sprite{
public:
	SDL_Texture * m_texture;
	SDL_Rect	m_size;
	
	int			m_totalFrame;	// TODO: dat total frame khi doc file len
	SDL_Rect    m_frames[16];

	Sprite(const char* NameSprite, const char* SpriteConfig);
	void renderFrame(int index, int posX, int posY);
};