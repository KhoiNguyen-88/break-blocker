#pragma once

class Texture
{
public:
	SDL_Texture*	m_texture;
	SDL_Rect		m_size;

	Texture();
	bool Load(const char* path);
};