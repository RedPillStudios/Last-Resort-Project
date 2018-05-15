#ifndef ENEMYLAMELLA_H
#define ENEMYLAMELLA_H

#include "Enemy.h"
#include "Animation.h"

struct SDL_Texture;

class EnemyLamella : public Enemy {

public:

	EnemyLamella(int x, int y, bool powerUp);
	void Move();

private:

	Animation LamellaAnim;
	uint lastPosX;
	uint lastPosY;
};

#endif