#ifndef MODULEPOWERUP_H
#define MODULEPOWERUP_H

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleSound.h"
#include "p2Point.h"
#include "ModuleCollision.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "ModuleRender.h"

#define ENEMIES_WEAPON 10
#define ENEMIES_SPEED 5
#define MAX_POWERUP 10



struct SDL_Texture;



enum POWERUP_TYPES {
	NON,
	BLUE,
	RED,
	LASER,
	SPEED
};

struct PowerUpInfo {

	POWERUP_TYPES type = POWERUP_TYPES::NON;
	int x, y;

};

class powerUp {
public:

	SDL_Texture * sprite = nullptr;
	powerUp(int x, int y) : position(x, y) {};
	~powerUp() {
		if (collider != nullptr)
			collider->to_delete = true;
	}
	Animation *animation = nullptr;
	Collider *collider = nullptr;


	const Collider* GetCollider() const {
		return collider;
	}

	virtual void Draw(SDL_Texture *sprites) {

		if (collider != nullptr)
			collider->SetPos(position.x, position.y);

		if (animation != nullptr)
			App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
	};

	virtual void Move() {};
	virtual void OnCollision(Collider *c1) {};
	fPoint position;
	POWERUP_TYPES type;


};



class powerUp_red : public powerUp {
public:

	powerUp_red(int x, int y);
	~powerUp_red() {};
	void Move() {};
	void OnCollision(Collider *c1) {};
	Animation Blue;
	Animation Red;
	fPoint position;

private:

	POWERUP_TYPES a;

};

class powerUp_Laser : public powerUp {
public:

	powerUp_Laser(int x, int y);
	~powerUp_Laser() {};
	void Move() {};
	void OnCollision(Collider *c1) {};
	Animation ChangeColor;
	fPoint position;

private:

	POWERUP_TYPES a;

};


class ModulePowerUp : public Module {

public:

	ModulePowerUp();
	~ModulePowerUp();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

public:

	int HOU_position_x;
	int HOU_position_y;
	bool fixed;

	bool HOU_activated;
	//void PowerUpAppear();

	SDL_Texture *HOU_Texture;

	SDL_Texture *Charge_texture;

	Mix_Chunk *PickUpSpeed;
	Mix_Chunk *PickUpWeapon;

	Collider *colliderHUB = nullptr;

	//animation sequences HOU
	Animation HOU_Front;
	Animation HOU_Front_Up;
	Animation HOU_Front_Down;
	Animation HOU_Back;
	Animation HOU_Back_UP;
	Animation HOU_Back_Down;
	Animation HOU_Down;
	Animation HOU_UP;
	Animation Charge;

	Animation *Power_Up_animation = nullptr;
	Animation *current_animation = nullptr;
	Animation *Charge_animation = nullptr;

	bool AddPowerUp(POWERUP_TYPES type, int x, int y);
	void OnCollision(Collider *c1, Collider *c2);
	void spawnPowerUp(const PowerUpInfo &info);

	PowerUpInfo queue[MAX_POWERUP];
	powerUp* PowerUps[MAX_POWERUP];

};

#endif