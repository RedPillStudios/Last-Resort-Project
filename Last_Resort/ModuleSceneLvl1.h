#ifndef __MODULESCENELVL1_H__
#define __MODULESCENELVL1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")


struct SDL_Texture;
struct Collider;
struct Mix_Chunk;

class ModuleSceneLvl1 : public Module
{
public:
	ModuleSceneLvl1();
	~ModuleSceneLvl1();

	bool Start();
	update_status Update();
	bool CleanUp();


public:
	
	SDL_Texture* graphics = nullptr; 
	SDL_Texture* graphics_Boss_Static_Background = nullptr;
	SDL_Texture* graphics_ThirdPlaneBackground = nullptr;
	SDL_Texture* graphics_SecondPlaneBackground = nullptr;
	SDL_Texture* graphics_FirstPlaneBackGround = nullptr;
	SDL_Texture* graphics_Crater_Boss_Zone = nullptr;

	SDL_Rect ThirdPlaneBackground;
	SDL_Rect SecondPlaneBackground;
	SDL_Rect FirstPlaneBackGround;
	SDL_Rect CraterBossZone;
	SDL_Rect Ball;

	Collider *BallCollider;
	//Music
	Mix_Music*Stage1 =  nullptr;

public: //movement of the firstplanebackground
	
	float FirstPlaneBackGround_position_X = 0;
	float SecondPlaneGround_position_X = 0;
	float ThirdPlaneBackground_position_X = 0;

	float ScrollingSpeed_Foreground=1.0f;
};

#endif