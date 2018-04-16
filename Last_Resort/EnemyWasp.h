#ifndef ENEMYWASP_H
#define ENEMYWASP_H

#include "Enemy.h"
#include "Animation.h"

struct SDL_Texture;

class EnemyWasp : public Enemy {

private:
	
	Animation *AnimWasp;

public:

	EnemyWasp(int x, int y);
	
};


#endif