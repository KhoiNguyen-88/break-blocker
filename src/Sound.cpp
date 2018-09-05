#include "Header.h"

bool Sound::Load(const char * path)
{
	//Load Sound Effect
	m_chunk = Mix_LoadWAV(path);

	if (m_chunk == NULL)
	{
		printf("%s", Mix_GetError());
		return false;
	}

	return true;
}

void Sound::Play(int times)
{
	if (m_playChannel == -1)
	{
		m_playChannel = Mix_PlayChannel(times, m_chunk, 0);
	}
	else
	{
		if (!Mix_Playing(m_playChannel))
			m_playChannel = Mix_PlayChannel(times, m_chunk, 0);
	}
}

void Sound::Stop()
{
	if (m_playChannel != -1)
	{
		Mix_HaltChannel(m_playChannel);
		m_playChannel = -1;
	}
}

Sound::Sound() : m_chunk(NULL), m_playChannel(-1)
{

}

