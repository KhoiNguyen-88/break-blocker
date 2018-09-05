#include "Header.h"

bool Music::LoadMusic(const char * path)
{
	//Load Music Effect
	m_music = Mix_LoadMUS(path);

	if (m_music == NULL)
	{
		printf("%s", Mix_GetError());
		return false;
	}

	return true;
}

void Music::PlayMusic()
{
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(m_music,-1);
	}
	else {
		this->PauseMusic();
	}
}

void Music::PauseMusic()
{
	if (Mix_PlayingMusic() == 1)
	{
		if (Mix_PausedMusic() == 1)
		{
			Mix_ResumeMusic();
		}
		else {
			Mix_PauseMusic();
		}
	}
}

void Music::StopMusic()
{
	Mix_HaltMusic();
}

Music::Music() : m_music(NULL)
{
}


Music::~Music()
{
}
