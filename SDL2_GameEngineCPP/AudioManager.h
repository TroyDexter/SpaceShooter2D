#pragma once

#include <SDL_mixer.h>
#include <vector>
#include <iostream>

using namespace std;


class AudioManager
{
private:
	//vector<Mix_Music*> musicTracks;
	vector<Mix_Chunk*> soundChunks;


public:
	AudioManager();
	~AudioManager();

	bool InitAudioManager();

	void LoadSound(const char* path);

	void PlaySound(int id, int channel=-1, int loops = 0);
	
	void UnloadAllSoundChunks();
	
};

