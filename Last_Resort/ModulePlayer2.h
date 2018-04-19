#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;
struct Mix_Chunk;

class ModulePlayer2 : public Module
{
public:
	ModulePlayer2();
	~ModulePlayer2();

	
	update_status Update();
	
	void OnCollision(Collider *c1, Collider *c2);
	

public://bools
	bool Start();
	bool CleanUp();
	bool AppearAnim;
	bool Dead;
	bool Player2Activated = false;
	bool ToBeDestroyed = false;
public:


	SDL_Rect Ship2;

	SDL_Texture* graphicsp2 = nullptr;

	Animation Up;
	Animation Down;
	Animation Appear;
	Animation Standard;
	Animation idle;
	Animation DestroyShip;

	Animation* current_animation2 = nullptr;

	iPoint positionp2;

	Collider *Ship2Collider;

public:

	uint lives = 3;

public:

	bool startAnim = true;
	bool shooted = false;

	Mix_Chunk*Shot_Sound = nullptr;


public:

	SDL_Rect setFirePos2() {

		SDL_Rect FirePos2;

		FirePos2.x = positionp2.x + 31;
		FirePos2.y = positionp2.y + 1;

		return FirePos2;
	}

	void resetPosition2() {
		positionp2.x = 20;
		positionp2.y = SCREEN_HEIGHT / 4;

	};
};

#endif
