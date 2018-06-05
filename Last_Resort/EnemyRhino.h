#ifndef __ENEMY_RHINO_H__
#define __ENEMY_RHINO_H__

#include "Enemy.h"

class Enemy_Rhino : public Enemy
{
private:

	float wave = -90.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;
	


public:
	bool hit;
	int counter;
	virtual void OnCollision(Collider *collider) override;
	Enemy_Rhino(int x, int y,bool powerUp, ENEMY_TYPES type_);
	void Move();

	SDL_Texture* Damaged;
	SDL_Texture* Normal;
	
};

#endif // __ENEMY_REDBIRD_H__