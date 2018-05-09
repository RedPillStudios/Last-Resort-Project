#ifndef ENEMYZICZAC__H_
#define ENEMYZICZAC__H_

#include "Enemy.h"
#include "Animation.h"

struct SDL_Texture;

class EnemyZicZac : public Enemy {

private:

	Animation AnimZicZac;
	Collider *EnemyZicZacCollider;
	bool going_up = true;
	float wave=90.0f;
	int original_y = 0;

public:

	EnemyZicZac(int x, int y,bool powerUp);
	void Move();

};


#endif