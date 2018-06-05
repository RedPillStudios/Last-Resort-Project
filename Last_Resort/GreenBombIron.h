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
	void OnCollision(Collider *c1, Collider *c2);

	iPoint PlayerPosition;
	int counter = 0;
	int counter2 = 0;

	bool up_, down_;

private:
	Animation GreenBombAnim;
	


};

#endif 