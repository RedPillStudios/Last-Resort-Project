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
enum STAGES {

	Stage1,
	Stage2,
	Stage3
};

class ModuleBossLvl1 : public Module {

public:

	ModuleBossLvl1();
	~ModuleBossLvl1();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	STAGES Stage;
public:


	//All colliders and animations
	Collider *Bot = nullptr;
	Collider *Eye = nullptr;
	Collider *Head = nullptr;
	Collider *Left_Arm = nullptr;
	Collider *Body = nullptr;
	//Appear
	Animation AppearAnim0;
	Animation AppearAnim;

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
	Animation *currentAppear = nullptr;
	Animation *currentAppear0 = nullptr;
	//Texture and position
	SDL_Texture *Boss = nullptr;
	SDL_Texture *AppearText = nullptr;
	SDL_Texture *Damaged = nullptr;
	SDL_Texture *Normal = nullptr;

	iPoint position;
	
public:
	bool BossMoves = false;
	bool boss1life = false;
	bool beAttacked;
	void OnCollision(Collider *c1, Collider *c2);
	bool dead;
	bool EyeBool = true;
	bool TimeCounter = true;
	bool TimeCounter2 = true;
	//booleans for movement
	bool ReachPos = false;
	//Booleans for charge attack
	bool ChargeAttack = false;
	bool Left = false;
	bool Right = false;
	bool Shooted = false;
	bool Forward = false;
	bool Backward = false;
	bool EndCharge = false;
	bool NeedToDisableBoss = false;
	bool hit = false;

public:
	uint life;
	uint AppearTime;
	uint AppearTime2;
	uint current_time = SDL_GetTicks();
	uint BossTrote = 1;
	uint TearShoot = 1;
	uint EnemyAddController = 0;
	uint PeeLimit = 0;
	uint positionXcorrector = -30;
	int BossTroteDelay;
	int TearShootDelay;
	int Timer1 = 0;
	int Time1 = 0;
	int Time2 = 0;
	int Time3 = 0;
	int Time4 = 0;
	int Time5 = 0;
	int Time6 = 0;
	int Time7 = 0;
	int Time8 = 0;
	int Time9 = 0;
	int Restartcontroller = 0;
	int Restartcontroller2 = 0;
	int Restartcontroller3 = 0;
	int Restartcontroller4 = 0;
	int Restartcontroller5 = 0;
	int Restartcontroller6 = 0;
	int Restartcontroller7 = 0;
	int Restartcontroller8 = 0;
	int ShootCounter = 0;
	int Controller1 = 0;
	int cicle = 2;
	int MaleTears;
	int randnum = 0;
	int counter_Flicker = 0;
public:

	

	//Attack Functions
	void Charge();
	void Shooting();
	void LluviaDorada();
	

	 
};

#endif