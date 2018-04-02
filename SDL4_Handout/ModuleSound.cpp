#include "Globals.h"
#include "Application.h"
#include "ModuleSound.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")



ModuleSound::ModuleSound() :Module()
{



}


 ModuleSound::~ModuleSound()
{


}

bool ModuleSound::Init()
{




}

bool ModuleSound::CleanUp()
{




}


Mix_Music*const ModuleSound::LoadMusic(const char*path)
{





}
Mix_Chunk*const ModuleSound::LoadChunk(const char*path)
{





}