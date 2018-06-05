#ifndef FIRE_SPEED_H
#define FIRE_SPEED_H

#include "Enemy.h"
#include "Animation.h"


struct SDL_Texture;

class FireSpeed :public Enemy
{
public:

	FireSpeed(int x, int y);
	void Move();

private:

	Animation Fire;
	bool Up;

	int counter = 0;

};


#endif // !1
