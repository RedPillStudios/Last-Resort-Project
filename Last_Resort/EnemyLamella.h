#ifndef ENEMYLAMELLA_H
#define ENEMYLAMELLA_H

#include "Enemy.h"
#include "Animation.h"
#include "ModuleCollision.h"

struct SDL_Texture;

class EnemyLamella : public Enemy {

public:

	EnemyLamella(int x, int y, bool powerUp, ENEMY_TYPES type_);
	void Move();

private:

	int StartAttack;
	int changeCollider;

	COLLIDER_TYPE typeColl;

	bool reachPosition = false;
	
	iPoint PlayerPosition;

	Animation Despawing;
	Animation Arriving;
	Animation Apearing;
	Animation LamellaAnim;
	uint lastPosX;
	uint lastPosY;
};

#endif

