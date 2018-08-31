#pragma once
class Sound
{
public:
	Mix_Chunk * m_chunk;
	bool Load(const char* path);
	Sound();
	~Sound();
};

