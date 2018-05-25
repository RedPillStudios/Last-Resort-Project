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

	Animation*Current_AnimationBody;


	Collider*body = nullptr;
	Collider*LArm = nullptr;
	Collider*RArm = nullptr;


	iPoint position;

public:
	iPoint PlayerPosition;
	uint life;
	uint movingTiming;
	uint moving_waiting;
	
	int counter = 0;
	int LArmPosition;
	int RArmPosition;
	int YarmsPos;

	bool Rarmfalling;
	bool LArmfallinf;
	bool moving_Down = false;
	bool dead = false;
	bool moveIron_Craw =false;
	bool bombsOut;
	bool armsOut;
	bool armsOut2;

	void bombs();
	void Move();
	void OnCollision(Collider *c1, Collider *c2);



};


#endif // !1