#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleSceneLvl1.h"

struct SDL_Texture;
struct Collider;
struct Mix_Chunk;

enum Shoots
{
	BASICSHOOT,
	BASICLASERSHOOT,
	LASERSHOOT,
	MISSILES,
	LASERSHOOTAREA,
	MISSILES2,
	BOMBSHOOT
};

class ModulePlayer : public Module
{
public:

	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider *c1, Collider *c2);
	
	bool AppearAnim;
	bool Dead;

	bool GOD = false;
	bool ToBeDeleted = false;
	
public:

	SDL_Rect Ship;
	SDL_Rect UI_ship;

	SDL_Texture* graphicsp1 = nullptr;
	SDL_Texture* Entry_God = nullptr;
	SDL_Texture* Normal = nullptr;

	Animation Up;
	Animation Down;
	Animation Appear;
	Animation Standard;
	Animation idle;
	Animation DestroyShip;

	Animation* current_animation = nullptr;
	
	iPoint position;

	Collider *Ship1Collider;

	//Timer
	float speed;
	int ShootTimer1;
	int ShootTimer2;
	int ShootTimer3;
	int ShootTimer4;
	int counterApearing;
	bool flickering;

public:
	
	bool startAnim = true;
	bool shooted = false;
	
	Mix_Chunk*Shot_Sound=nullptr;
	Mix_Chunk*MissilePower_Sound = nullptr;
	Mix_Chunk*LasserBeam_Sound = nullptr;

public:

	SDL_Rect setFirePos() {

		SDL_Rect FirePos;
		
		FirePos.x = position.x + 31;
		FirePos.y = position.y + 1;

		return FirePos;
	}

		void resetPosition() {
			position.x = App->scene1background->position_min_limit + 20;
		    position.y = SCREEN_HEIGHT / 2;

	}
		void Reset_limits(){
			int position_max_limit = SCREEN_WIDTH;
			int position_min_limit = 0;
		}
public:

	//shoot selector here
	int WeaponType = 0;
	void ShootSelector(uint shoot);

	//POWERUP Levels
	bool Lvl0 = true;
	bool Lvl1 = false;
	bool Lvl2 = false;
	bool Lvl3 = false;
};

#endif