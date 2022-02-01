#include "AudioManager.h"

AudioManager::AudioManager()
{
	
}


bool AudioManager::InitAudioManager()
{
	if(Mix_Init(MIX_INIT_MP3) == 0)
	{
		cout << "AudioManager Mixer Init failed\n";
		return false;
	}

	Mix_OpenAudio(22050,AUDIO_S16SYS, 2, 4096);
	Mix_AllocateChannels(16);
	return true;
}

void AudioManager::LoadSound(const char* path)
{
	//Step 1: Load the file we want to play as a sound chunk
	Mix_Chunk* t = Mix_LoadWAV(path);
	//Step 2: add to our vector of soundChunks
	if(t!=nullptr)
		soundChunks.push_back(t);
	else
		cout << "Sound load failed: " << path << endl;
}

void AudioManager::PlaySound(int id, int channel, int loops)
{
	if(!Mix_Playing(channel))
	{
		Mix_PlayChannel(channel, soundChunks[id], loops);
	}
	
}

void AudioManager::UnloadAllSoundChunks()
{
	//Mix_FreeChunk()
	//How do you unload an entire vector?
	//Iterate through the vector
	//unload each index by calling Mix_FreeChunk, and set its index to nullptr
	//after you complete the above steps,
	//clear the vector & shrink to fit
	for(int i = 0; i < soundChunks.size(); i++)
	{
		soundChunks[i] = nullptr;
		soundChunks.clear();
		soundChunks.shrink_to_fit();
	}
}

AudioManager::~AudioManager()
{
	UnloadAllSoundChunks();
	
	Mix_CloseAudio();
	Mix_Quit();
}

