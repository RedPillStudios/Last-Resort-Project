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
	
	void OnCollision(Collider *c1) {};
	
	Animation Red;
	fPoint position;


	

};

class powerUp_Laser : public powerUp {
public:

	powerUp_Laser(int x, int y);
	~powerUp_Laser() {};
	
	void OnCollision(Collider *c1) {};
	Animation ChangeColor;
	fPoint position;



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


	//int Angle;
	float HOU_Direction;
	float HOU_Speed=5;
	iPoint shipCenter;
	iPoint HOU_position;
	iPoint HOU_LastPosition;
	int HOU_Charge;


	bool Up;
	bool Down;
	bool Left;
	bool Right;
	bool Throw=false;
	bool Throwing=false;
	bool ReturnPosition=true;
	bool HOUreachPosition=false;
	bool charging;
	

	bool fixed;

	bool HOU_activated;
	//void PowerUpAppear();

	bool Charging_Sound_HOU = true;

	int timeSoundCharge;

	SDL_Texture *HOU_Texture;

	SDL_Texture *Charge_texture;

	Mix_Chunk *PickUpSpeed;
	Mix_Chunk *PickUpWeapon;

	Mix_Chunk *ChargeHOUSound;
	Mix_Chunk *ReleasedChargeHOUSound;

	Collider *colliderHUB = nullptr;

	//animation sequences HOU
	Animation HOU_Front;
	Animation HOU_Front_Up_Down;
	Animation HOU_Front_Up;
	Animation HOU_Front_Up_Up;
	Animation HOU_Front_Down_Up;
	Animation HOU_Front_Down;
	Animation HOU_Front_Down_Down;
	Animation HOU_Back;
	Animation HOU_Back_Up_Up;
	Animation HOU_Back_UP;
	Animation HOU_Back_Up_Down;
	Animation HOU_Back_Down_Down;
	Animation HOU_Back_Down;
	Animation HOU_Back_Down_Up;
	Animation HOU_Down;
	Animation HOU_UP;
	Animation Charge;
	Animation Throw_Ball;


	Animation *Power_Up_animation = nullptr;
	Animation *current_animation = nullptr;
	Animation *Charge_animation = nullptr;

	bool AddPowerUp(POWERUP_TYPES type, int x, int y);
	void OnCollision(Collider *c1, Collider *c2);
	void spawnPowerUp(const PowerUpInfo &info);
	void throwHOU();
	void returnHOU();
	void Hou_Movement();

	PowerUpInfo queue[MAX_POWERUP];
	powerUp* PowerUps[MAX_POWERUP];

};

#endif