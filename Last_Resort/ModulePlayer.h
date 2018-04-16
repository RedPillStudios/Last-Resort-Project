#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"


struct SDL_Texture;
struct Collider;
struct Mix_Chunk;

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


public:
	SDL_Rect Ship;
	SDL_Texture* graphicsp1 = nullptr;

	Animation Up;
	Animation Down;
	Animation Appear;
	Animation Standard;
	Animation idle;
	Animation DestroyShip;

	Animation* current_animation = nullptr;
	
	iPoint position;

	Collider *Ship1Collider;
	

public:

	bool startAnim = true;
	bool shooted = false;
	bool PlayerActived = false;


	Mix_Chunk*Shot_Sound=nullptr;


public:

	SDL_Rect setFirePos() {

		SDL_Rect FirePos;
		
		FirePos.x = position.x + 31;
		FirePos.y = position.y + 1;

		return FirePos;
	}

		void resetPosition() {
		position.x = 20;
		position.y = SCREEN_HEIGHT / 2;

	};
};

#endif