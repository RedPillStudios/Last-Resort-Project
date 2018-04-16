#ifndef MODULEPOWERUP_H
#define MODULEPOWERUP_H

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleSound.h"

#include "SDL_mixer/include/SDL_mixer.h"

#define ENEMIES_WEAPON 10
#define ENEMIES_SPEED 5

struct SDL_Texture;

class ModulePowerUp : public Module {

public:

	ModulePowerUp();
	~ModulePowerUp();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	void IsPicked(Collider *c1, Collider *c2);
	void PowerUpAppear();

	SDL_Rect Power_Up_Weapon;
	SDL_Rect Power_Up_Speed;
	SDL_Texture *powerup;

	Mix_Chunk *PickUpSpeed;
	Mix_Chunk *PickUpWeapon;

	Collider *colliderWeapon = nullptr;
	Collider *colliderSpeed = nullptr;
	Animation Anim_Weapon;
};

#endif