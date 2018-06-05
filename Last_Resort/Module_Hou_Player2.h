#ifndef MODULE_HOU_PLAYER2_H
#define MODULE_HOU_PLAYER2_H

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleSound.h"
#include "p2Point.h"
#include "ModuleCollision.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "ModuleRender.h"


struct SDL_Texture;



class ModuleHouPlayer2 : public Module {

public:

	ModuleHouPlayer2();
	~ModuleHouPlayer2();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	float HOU_Direction;
	float HOU_Direction_Angle;
	float HOU_Speed = 5;
	iPoint shipCenter;
	iPoint HOU_position;
	iPoint HOU_LastPosition;
	iPoint FixedPosition;
	int HOU_Charge;

	bool Throw = false;
	bool Throwing = false;
	bool ReturnPosition = true;
	bool HOUreachPosition = false;
	bool charging;
	bool Red = false;
	bool Blue = false;

	bool fixed;

	bool HOU_activated;
	//void PowerUpAppear();

	bool Charging_Sound_HOU = true;

	int timeSoundCharge;

	SDL_Texture *HOU_Texture;

	SDL_Texture *Charge_texture;

	Mix_Chunk *ChargeHOUSound;
	Mix_Chunk *ReleasedChargeHOUSound;

	Collider *colliderHUB = nullptr;

	//Blue animation sequences HOU
	Animation Blue_HOU_Front;
	Animation Blue_HOU_Front_Up_Down;
	Animation Blue_HOU_Front_Up;
	Animation Blue_HOU_Front_Up_Up;
	Animation Blue_HOU_Front_Down_Up;
	Animation Blue_HOU_Front_Down;
	Animation Blue_HOU_Front_Down_Down;
	Animation Blue_HOU_Back;
	Animation Blue_HOU_Back_Up_Up;
	Animation Blue_HOU_Back_UP;
	Animation Blue_HOU_Back_Up_Down;
	Animation Blue_HOU_Back_Down_Down;
	Animation Blue_HOU_Back_Down;
	Animation Blue_HOU_Back_Down_Up;
	Animation Blue_HOU_Down;
	Animation Blue_HOU_UP;
	Animation Blue_Charge;
	Animation Blue_Throw_Ball;
	Animation blueball_charging;


	//Red animation sequences HOU
	Animation Red_HOU_Front;
	Animation Red_HOU_Front_Up_Down;
	Animation Red_HOU_Front_Up;
	Animation Red_HOU_Front_Up_Up;
	Animation Red_HOU_Front_Down_Up;
	Animation Red_HOU_Front_Down;
	Animation Red_HOU_Front_Down_Down;
	Animation Red_HOU_Back;
	Animation Red_HOU_Back_Up_Up;
	Animation Red_HOU_Back_UP;
	Animation Red_HOU_Back_Up_Down;
	Animation Red_HOU_Back_Down_Down;
	Animation Red_HOU_Back_Down;
	Animation Red_HOU_Back_Down_Up;
	Animation Red_HOU_Down;
	Animation Red_HOU_UP;
	Animation Red_Throw_Ball;

	Animation Redball_charging;

	int particlesTimmer;





	Animation *current_animation = nullptr;
	Animation *Blue_Charge_animation = nullptr;

	void OnCollision(Collider *c1, Collider *c2);
	void throwHOU();
	void returnHOU();
	void Hou_Movement();


};

#endif