#pragma once
class Music
{
	Mix_Music* m_music;

public:
	bool LoadMusic(const char * path);
	void PlayMusic();
	void PauseMusic();
	void StopMusic();
	Music();
	~Music();
};

