#ifndef GREENBOMBIRON__H
#define GREENBOMBIRON__H

#include "Enemy.h"
#include "Animation.h"


struct SDL_Texture;

class GreenBombIron :public Enemy
{
public:
	GreenBombIron(int x, int y);
	void Move();

	iPoint PlayerPosition;

private:
	Animation GreenBombAnim;


};

#endif 