#ifndef Enemy_Tears_
#define Enemy_Tears_

#include "Enemy.h"

class Enemy_BossTears : public Enemy
{
private:

	float wave = -90.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;
	bool bot = false;
	uint MovCounter = 0;
	int initialx;
	int velocityX = 3;
	float velocityY = 1;
	int Ylimit = 20;
	bool MovingDown = false;
	int a;
public:

	Enemy_BossTears(int x, int y, bool powerUp);
	void Move();

};

#endif
