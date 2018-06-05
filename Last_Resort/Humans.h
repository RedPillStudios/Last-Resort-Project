#ifndef HUMANS_H
#define HUMANS_H

#include "Enemy.h"
#include "Animation.h"


struct SDL_Texture;

class Humans:public Enemy
{
public:

	Humans(int x, int y);
	void Move();

private:

	Animation HumanAnimation;
	bool Up;

	int counter = 0;

};


#endif // !1
