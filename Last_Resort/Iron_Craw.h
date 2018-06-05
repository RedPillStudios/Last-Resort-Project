#ifndef IRON_CRAW__H
#define IRON_CRAW__H

#include "Module.h"
#include "p2Point.h"
#include "Animation.h"
#include "Globals.h"
#include <stdio.h>

#include "SDL/include/SDL.h"
#include "SDL/include/SDL_timer.h"
#include <stdlib.h>
#include "ModuleSceneLvl1.h"


#define MAX_HEIGHT_MINIBOSS 20
#define MIN_HEIGHT_MINIBOSS 85
#define PRESET_POSITION_IRON 55


struct Collider;
struct SDL_Texture;

enum attack {

	GREENBOMBS,

};

class Iron_Craw:public Module
{
public:
	Iron_Craw();
	~Iron_Craw();

	bool Start();

	update_status Update();

	bool CleanUp();

public:

	SDL_Texture*Mini_Boss;

	Animation idle;
	Animation idle_Damage;
	Animation Left_Arm;
	Animation Right_Arm;
	Animation leg1;
	Animation leg2;
	Animation blueCircle;
	Animation FirstIdle;

	Animation*Current_AnimationBody;


	Collider*body = nullptr;
	Collider*LArm = nullptr;
	Collider*RArm = nullptr;


	fPoint position;

public:
	iPoint PlayerPosition;
	uint life;
	uint movingTiming;
	uint moving_waiting;
	
	int counter = 0;
	float LArmPosition;
float RArmPosition;
	int YarmsPos;
	int explosionTiming;
	int counterIron;
	int counterGreenBomb;
	int MoveTiming;
	int MoveTiming2;
	int angleBomb;
	float SpawnPos;
	


	double radians;

	bool Rarmfalling;
	bool LArmfallinf;
	bool dead = false;
	bool moveIron_Craw =false;
	bool bombsOut;
	bool armsOut;
	bool armsOut2;
	bool dyingParticles = true;
	bool moving_Down;
	bool moving_Up ;
	bool launchBombs;
	bool SpawnFInished=false;
	bool spawnMovementDown;
	bool EnemyAppear;
	bool ExplosionDead;
	bool disablingIronCraw=false;

	void bombs();
	void Move();
	void spawn();

	void OnCollision(Collider *c1, Collider *c2);



};


#endif // !1