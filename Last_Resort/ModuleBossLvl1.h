#ifndef MODULEBOSSLVL1_H
#define MODULEBOSSLVL1_H

#include "Module.h"
#include "p2Point.h"
#include "Animation.h"
#include "Globals.h"
#include <stdio.h>

#include "SDL/include/SDL.h"
#include "SDL/include/SDL_timer.h"
#include <stdlib.h>
#include "ModuleSceneLvl1.h"

struct Collider;
struct SDL_Texture;

enum Attack {

	EYE,
	BODY,
	NONE
};

class ModuleBossLvl1 : public Module {

public:

	ModuleBossLvl1();
	~ModuleBossLvl1();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	//All colliders and animations
	Collider *Bot = nullptr;
	Collider *Eye = nullptr;
	Collider *Head = nullptr;
	Collider *Left_Arm = nullptr;
	Collider *Body = nullptr;

	//Eye
	Animation AnimOpenEye;
	Animation AnimCloseEye;
	Animation AnimClosedEye;

	//Mouth
	Animation AnimOpenMouth;
	Animation AnimCloseMouth;
	Animation AnimMouth;

	//Others
	Animation AnimBody;
	Animation AnimArm;
	Animation AnimPotbelly;

	Animation *current_eye = nullptr;
	Animation *current_head = nullptr;

	//Texture and position
	SDL_Texture *Boss = nullptr;
	iPoint position;
	
public:

	bool beAttacked;
	void OnCollision(Collider *c1, Collider *c2);
	uint life;
	bool dead;

	bool ShootSpawned;
	bool TimeCounter = true;
	bool TimeCounter2 = true;

	uint AppearTime;
	uint AppearTime2;
	uint current_time = SDL_GetTicks();

	bool BossMoves = false;
	bool boss1life = false;

public:

	//Booleans for charge attack
	bool ChargeAttack = false;
	bool Left = false;
	bool Right = false;

	//Attack Functions
	void Charge();
	void Shooting();
	

	 
};

#endif