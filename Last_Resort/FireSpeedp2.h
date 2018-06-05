#ifndef FIRE_SPEED_P2_H
#define FIRE_SPEED_P2_H

#include "Enemy.h"
#include "Animation.h"


struct SDL_Texture;

class FireSpeedp2 :public Enemy
{
public:

	FireSpeedp2(int x, int y);
	void Move();

private:

	Animation Fire;
	bool Up;

	int counter = 0;

};


#endif // !1
