#ifndef CARSTOFAST__H_
#define CARSTOFAST__H_

#include "Enemy.h"
#include "Animation.h"

struct SDL_Texture;

class CarsToFast:public Enemy
{
private:

	Animation Cars;

public:

	Animation CarRed;
	Animation CarYellow;
	Animation CarBlue;
	Animation CarRed_Destruct;
	Animation CarYellow_Destruct;
	Animation CarBlue_destruct;
	int randomColorCars = 0;
	bool WaitDead=false;

	CarsToFast(int x, int y,ENEMY_TYPES type_);
	virtual void OnCollision(Collider *collider) override;
	void Move();
};

#endif