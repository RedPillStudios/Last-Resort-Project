#ifndef __MODULESCENELVL1_H__
#define __MODULESCENELVL1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#include "SDL/include/SDL_timer.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "SDL/include/SDL.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")


struct SDL_Texture;
struct Collider;
struct Mix_Chunk;

class ModuleSceneLvl1 : public Module {

public:

	ModuleSceneLvl1();
	~ModuleSceneLvl1();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	int position_max_limit = SCREEN_WIDTH;
	int position_min_limit = 0;
	int timeFadeInt = SDL_GetTicks();

	bool IronCraw2 = false;
	bool IronCraw1 = false;
	bool spawned = false;
	bool counterfordisable = false;


public:
	
	SDL_Texture* graphics = nullptr; 
	SDL_Texture* graphics_Boss_Static_Background = nullptr;
	SDL_Texture* graphics_ThirdPlaneBackground = nullptr;
	SDL_Texture* graphics_SecondPlaneBackground = nullptr;
	SDL_Texture* graphics_FirstPlaneBackGround = nullptr;
	SDL_Texture* graphics_Crater_Boss_Zone = nullptr;
	SDL_Texture* Laser_Sprites = nullptr;
	SDL_Texture* graphics_Streetlight = nullptr;
	Animation minispaceships ;

	SDL_Rect ThirdPlaneBackground;
	SDL_Rect SecondPlaneBackground;
	SDL_Rect FirstPlaneBackGround;
	SDL_Rect CraterBossZone;

	Animation Bluelight;
	Animation YellowLight;
	Animation Streetlight;
	Animation Streetlight2;
	SDL_Texture* Minispaceship_texture = nullptr;

	int posCars = 0;
	int randomPositionCars = 0;
	int randomColorCars = 0;
	int xxx = 1;
	int yyy = 1;

	bool switchMusic = false;

	void StreetlightCreator();

	//Music
	Mix_Music*Stage1 =  nullptr;
	Mix_Music*Stage1_Boss_Music = nullptr;
};

#endif