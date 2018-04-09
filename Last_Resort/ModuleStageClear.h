#pragma once
#ifndef MODULESTAGECLEAR_H_
#define MODULESTAGECLEAR_H_

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleStageClear : public Module {
public:
	ModuleStageClear();
	~ModuleStageClear();

	bool Start();
	update_status Update();
	bool CleanUp();
public:
	

	SDL_Texture * graphics_StageClearImage = nullptr;

	SDL_Rect FirstPlaneImage;

};






#endif