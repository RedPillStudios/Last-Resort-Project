#ifndef MODULEPOWERUP_H
#define MODULEPOWERUP_H

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleSound.h"
#include "p2Point.h"

#include "SDL_mixer/include/SDL_mixer.h"

#define ENEMIES_WEAPON 10
#define ENEMIES_SPEED 5

struct SDL_Texture;

enum POWERUP_TYPES {

	BLUE,
	RED,
	SPEED
};

class ModulePowerUp : public Module {

public:

	ModulePowerUp();
	~ModulePowerUp();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	int HOU_position_x;
	int HOU_position_y;
	bool fixed;

	bool HOU_activated;
	void IsPicked(Collider *c1, Collider *c2);
	//void PowerUpAppear();
	
	iPoint PowerUpAppear_Position;

	SDL_Texture *HOU_Texture;

	SDL_Rect Power_Up_Weapon;
	SDL_Rect Power_Up_Speed;
	SDL_Texture *powerup;
	SDL_Texture *Charge_texture;

	Mix_Chunk *PickUpSpeed;
	Mix_Chunk *PickUpWeapon;

	Collider *colliderPowerUp = nullptr;
	Collider *colliderHUB = nullptr;
	
	Animation Power_Up;

	//animation sequences HOU
	Animation HOU_Front;
	Animation HOU_Back;
	Animation HOU_Down;
	Animation HOU_UP;
	Animation Charge;

	Animation *Power_Up_animation = nullptr;
	Animation *current_animation = nullptr;
	Animation *Charge_animation = nullptr;

	bool AddPowerUp(POWERUP_TYPES type, int x, int y);

	void OnCollision(Collider *c1, Collider *c2);
};

#endif