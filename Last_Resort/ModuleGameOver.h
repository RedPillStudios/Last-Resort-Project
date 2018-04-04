#ifndef __MODULEGAMEOVER_H__
#define __MODULEGAEMOVER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

class ModuleGameOver : public Module
{
public:
	ModuleGameOver();
	~ModuleGameOver();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture *graphics_GameOverImage;

	SDL_Rect Background;
	SDL_Rect GameOverImage;

	Mix_Music *GameOver = nullptr;
};


#endif
