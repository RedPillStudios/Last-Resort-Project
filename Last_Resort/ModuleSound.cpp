#include "Globals.h"
#include "Application.h"
#include "ModuleSound.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

ModuleSound::ModuleSound() :Module()
{
	for (uint i = 0; i < MAX_MUSIC; ++i)
		music[i] = nullptr;

	for (uint i = 0; i < MAX_CHUNKS; ++i)
		chunks[i] = nullptr;

	

}


 ModuleSound::~ModuleSound()
{ }

bool ModuleSound::Init()
{
	LOG("Init Sound Library");
	bool ret=true;
	
	//Initialize SDL_mixer 
	int flags = Mix_Init(MIX_INIT_OGG);
	
	if (!flags)
	{
	LOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		ret = false;
	}

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	
	return ret;

}

update_status ModuleSound::Update() {

	if (!Playing)
	{
		Mix_PlayMusic(music[0],-1);//not sure about this line
		Playing = true;

	}

	return UPDATE_CONTINUE;
};



bool ModuleSound::CleanUp()
{
	LOG("Freeing Music and Chunks library");

	for (uint i = 0; i < MAX_MUSIC; ++i)
		if (music[i] != nullptr) {
			Mix_FreeMusic(music[i]);
		music[i] = nullptr;
		}

	for (uint i = 0; i < MAX_CHUNKS; ++i)
		if (chunks[i] != nullptr) {
			Mix_FreeChunk(chunks[i]);
			chunks[i] = nullptr;
		}

	Mix_CloseAudio();
	Mix_Quit();
	return true;

}


Mix_Music*const ModuleSound::LoadMusic(const char*path)
{
	Mix_Music*musicSound=nullptr;

	

	//To load music we call Mix_LoadMUS
	bool ret = true;
	
	musicSound = Mix_LoadMUS(path);
	if (!musicSound)
	{

		LOG("Unable to create music from path! SDL Error: %s\n",SDL_GetError());
		ret = false;
	}


	return musicSound;

}

Mix_Chunk*const ModuleSound::LoadChunk(const char*path)
{
	
	
	Mix_Chunk*chunks=nullptr;

	bool ret=true;

	//To load sound effect we call Mix_LoadWAV

	chunks = Mix_LoadWAV(path);
	
	if (chunks == nullptr)
	{
		LOG("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		ret = false;
	}


	return chunks;
}