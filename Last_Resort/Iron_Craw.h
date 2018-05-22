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

	uint life;
	bool dead = false;

	void bombs();
	void Move();
	void OnCollision(Collider *c1, Collider *c2);



};


#endif // !1