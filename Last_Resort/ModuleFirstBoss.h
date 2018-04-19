#ifndef __MODULEFIRSTBOSS_H__
#define __MODULEFIRSTBISS_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleParticles.h"


struct SDL_Texture;
struct Collider;
struct Mix_Chunk;

class ModuleBoss : public Module
{
public:
	ModuleBoss();
	~ModuleBoss();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider *c1, Collider *c2);

	bool AppearAnim;
	bool Dead;


public:

	SDL_Rect Ship;
	SDL_Texture* Boss_Texture = nullptr;

	Animation Right_Arm;
	Animation Body;
	Animation centerMachine;
	Animation idle;
	Animation DestroyShip;

	Animation*Head_current_animation = nullptr;
	Animation Head_Standard;
	Animation Head_Open;
	Animation Head_Close;

	Animation*Eye_current_animation = nullptr;
	Animation Open_Eye;
	Animation Idle_Eye;
	Animation Close_Eye;


	Animation* current_animation = nullptr;

	iPoint position;

	Collider *Ship1Collider;


public:

	Mix_Chunk*Shot_Sound = nullptr;

public:



#endif