#ifndef ENEMYWASP_H
#define ENEMYWASP_H

#include "Enemy.h"
#include "Animation.h"

struct SDL_Texture;

class EnemyWasp : public Enemy {

private:
  
	Animation AnimWasp;
	/*Collider *EnemyWaspCollider;*/
	

public:

	EnemyWasp(int x, int y,bool powerUp);
	void Move();
	
};


#endif