#ifndef __MODULESCENELVL2_H__
#define __MODULESCENELVL2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

struct SDL_Texture;

class ModuleSceneLvl2 : public Module
{

public:

	ModuleSceneLvl2();
	~ModuleSceneLvl2();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture *graphics_Background = nullptr;
	SDL_Texture *graphics_Mid = nullptr;

	SDL_Rect Background;
	SDL_Rect Foreground;

	Mix_Music *Stage2 = nullptr;

public:

	float Background_position_X = 0;
	float Foreground_position_X = SCREEN_WIDTH*3;

};

#endif