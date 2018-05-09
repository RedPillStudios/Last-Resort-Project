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
	int randomColorCars = 0;

	CarsToFast(int x, int y);
	void Move();
};

#endif