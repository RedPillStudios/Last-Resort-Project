#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

struct Mix_Chunk;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Rect Ship;
	SDL_Texture* graphics = nullptr;
	Animation Up;
	Animation Down;
	Animation Appear;
	Animation Standard;
	Animation idle;
	iPoint position;
	bool startAnim = true;
	bool shooted = false;

	Mix_Chunk*Shot_Sound=nullptr;

	SDL_Rect setFirePos() {

<<<<<<< HEAD
	SDL_Rect setFirePos() {

		SDL_Rect FirePos;

		FirePos.x = position.x + 31;
		FirePos.y = position.y + 1;

=======
		SDL_Rect FirePos;
		
		FirePos.x = position.x + 31;
		FirePos.y = position.y + 1;

>>>>>>> 1c86c53941fb8c09e988835da4c7a9f88d188c2a
		return FirePos;
	}

		void resetPosition() {
		position.x = 20;
		position.y = SCREEN_HEIGHT / 2;

	}

};

#endif