#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 17

//Scene 2 is not here!!

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
class ModuleMainMenu;
class ModuleGameOver;
class ModuleParticles;
class ModuleStageClear;
class ModuleCollision;
class ModuleEnemies;
class ModulePowerUp;
class ModuleFonts;

class ModulePlayer2;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleMainMenu *menu;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleSceneLvl1* scene1background;
	ModuleStageClear *stageclear;
	ModulePlayer* player;
	ModuleSound* sound;
	ModuleFadeToBlack *fade;
	ModuleGameOver *gameover;
	ModuleParticles *particles;
	ModuleCollision *collision;
	ModuleEnemies *enemies;
	ModulePowerUp *powerup;
	ModulePlayer2 *player2;
	ModuleFonts *fonts;
	

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