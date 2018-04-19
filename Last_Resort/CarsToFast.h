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

	CarsToFast(int x, int y);
	void Move();
};

#endif