#include "Header.h"

Texture::Texture() : m_texture(NULL)
{
}

bool Texture::Load(const char * path)
{
	m_texture = IMG_LoadTexture(Shared::m_renderer, path);

	if (!m_texture)
	{
		SDL_Log("Unable to load texture: %s. Error: %s", path, IMG_GetError());
		return false;
	}

	SDL_QueryTexture(m_texture, NULL, NULL, &m_size.w, &m_size.h);
	return true;
}
