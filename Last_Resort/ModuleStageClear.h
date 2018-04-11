#pragma once
#ifndef MODULESTAGECLEAR_H_
#define MODULESTAGECLEAR_H_

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleSound.h"
#include "SDL_image\include\SDL_image.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

class ModuleStageClear : public Module {

public:
	ModuleStageClear();
	~ModuleStageClear();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	Mix_Music* StageClear = nullptr;
	SDL_Texture* graphics_StageClearImage = nullptr;
	SDL_Rect FirstPlaneImage;
	
};

#endif
