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
public:
	SDL_Rect Ship;
	SDL_Rect Ship2;

	SDL_Texture* graphics = nullptr;

	Animation Up;
	Animation Down;
	Animation Appear;
	Animation Standard;
	Animation idle;
	Animation DestroyShip;

	Animation* current_animation = nullptr;
	Animation* current_animation2 = nullptr;

	iPoint position;
	iPoint positionp2;

	Collider *Ship1Collider;
	Collider *Ship2Collider;
	

public:

	bool startAnim = true;
	bool shooted = false;

	Mix_Chunk*Shot_Sound=nullptr;


public:

	SDL_Rect setFirePos() {

		SDL_Rect FirePos;
		
		FirePos.x = position.x + 31;
		FirePos.y = position.y + 1;

		return FirePos;
	}

	SDL_Rect setFirePos2() {

		SDL_Rect FirePos2;

		FirePos2.x = positionp2.x + 31;
		FirePos2.y = positionp2.y + 1;

		return FirePos2;
	}

		void resetPosition() {
		position.x = 20;
		position.y = SCREEN_HEIGHT / 2;

	};
		void resetPosition2() {
			positionp2.x = 20;
			positionp2.y = SCREEN_HEIGHT / 4;

		};
};

#endif