#ifndef ENEMYSUICIDE__H_
#define ENEMYSUICIDE__H_

#include "Enemy.h"
#include "Animation.h"

class EnemySuicide:public Enemy{

private:

	Animation AnimSuicide;

public:

	EnemySuicide(int x, int y);
	void Move();


};



#endif // !ENEMYSUICIDE__H_