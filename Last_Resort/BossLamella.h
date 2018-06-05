#ifndef ENEMYBOSSLAMELLA_H
#define ENEMYBOSSLAMELLA_H

#include "Enemy.h"
#include "Animation.h"
#include "ModuleCollision.h"

struct SDL_Texture;

class EnemyBossLamella : public Enemy {

public:

	EnemyBossLamella(int x, int y, bool powerUp);
	void Move();

public:

	virtual void OnCollision(Collider *collider) override;

	Animation MovingAnim;
	Animation HittedAnim;
	iPoint PlayerPosition;

	int counter = 0;
	SDL_Texture* Normal;
	bool hit;
	//int counter2;

	
};

#endif

