#ifndef ENEMYWASP_H
#define ENEMYWASP_H

#include "Enemy.h"
#include "Animation.h"


class EnemyWasp : public Enemy {

private:
  
	Animation AnimWasp;

public:
	
	EnemyWasp(int x, int y,bool powerUp);
	void Move();
	
};


#endif