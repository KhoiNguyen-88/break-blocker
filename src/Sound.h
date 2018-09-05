#pragma once
class Sound
{
	Mix_Chunk* m_chunk;
	int m_playChannel;

public:
	Sound();
	~Sound();

	bool Load(const char* path);
	void Play(int times);
	void Stop();

};

