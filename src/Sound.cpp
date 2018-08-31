#include "Header.h"

bool Sound::Load(const char * path)
{
	//Load Sound Effect
	m_chunk = Mix_LoadWAV(path);

	if (m_chunk == NULL)
	{
		printf("%s", Mix_GetError());
		return -1;
	}

	return false;
}

Sound::Sound() : m_chunk(NULL)
{

}

