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
	MISILES,
	LASER,
	SPEED,
	BOMB
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
	bool ColorRed;
	bool ColorBlue;

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

	virtual void Update() {};
	virtual void OnCollision(Collider *c1) {};
	fPoint position;
	POWERUP_TYPES type;
};

class powerUp_Misiles : public powerUp {
public:

	powerUp_Misiles(int x, int y);
	~powerUp_Misiles() {};
	
	void OnCollision(Collider *c1) {};
	void Update();

	Animation Red;
	Animation Blue;
	fPoint position;

	int timing;
};

class powerUp_Laser : public powerUp {
public:

	powerUp_Laser(int x, int y);
	~powerUp_Laser() {};
	
	void OnCollision(Collider *c1) {};
	Animation Red;
	Animation Blue;
	Animation ChangeColor;
	fPoint position;

	void Update();

	int timing;

};

class powerUp_Bomb : public powerUp {

public:

	powerUp_Bomb(int x, int y);
	~powerUp_Bomb() {};

	void OnCollision(Collider *c1) {};
	Animation Red;
	Animation Blue;
	Animation ChangeColor;
	fPoint position;

	void Update();
	int timing;

};

class powerUp_Speed : public powerUp {

public:

	powerUp_Speed(int x, int y);
	~powerUp_Speed() {};

	void OnCollision(Collider *c1) {};
	Animation Speed;
	fPoint position;

	void Update() {};
	int timing;

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

	//Mix_Chunk *PickUpSpeed;
	Mix_Chunk *PickUpWeapon;

	Animation *Power_Up_animation = nullptr;
	Animation *current_animation = nullptr;

	bool AddPowerUp(POWERUP_TYPES type, int x, int y);
	void OnCollision(Collider *c1, Collider *c2);
	void spawnPowerUp(const PowerUpInfo &info);

	PowerUpInfo queue[MAX_POWERUP];
	powerUp* PowerUps[MAX_POWERUP];

};

#endif