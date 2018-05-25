#ifndef __MODULEMAINMENU_H__
#define __MODULEMAINMENU_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")


class ModuleMainMenu : public Module {

public:

	ModuleMainMenu();
	~ModuleMainMenu();

	bool Start();
	update_status Update();
	bool CleanUp();

	SDL_Texture *graphics_Background = nullptr;
	SDL_Rect Background;
	Mix_Music *Main_Menu = nullptr;

};

#endif