#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 11

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleSceneLvl1;
class ModulePlayer;
class ModuleSound;
class ModuleFadeToBlack;
class Module;
class ModuleSceneLvl1;
class ModuleSceneLvl2;
class ModuleMainMenu;
class ModuleGameOver;

class Application
{
public:

	Module* modules[NUM_MODULES] = { nullptr };
	ModuleWindow* window = nullptr;
	ModuleMainMenu *menu = nullptr;
	ModuleRender* render = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleSceneLvl1* scene1background = nullptr;
	ModulePlayer* player = nullptr;
	ModuleSound* sound = nullptr;
	ModuleFadeToBlack *fade = nullptr;
	ModuleSceneLvl2 *scene2background = nullptr;
	ModuleGameOver *gameover = nullptr;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__