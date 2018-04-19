#ifndef ENEMY_H
#define ENEMY_H

#include "p2Point.h"
#include "Animation.h"
#include "ModuleTextures.h"

struct SDL_Textures;
struct Collider;

class Enemy {

protected:

	Animation *animation = nullptr;
	Collider *collider = nullptr;


public:

	fPoint position;
	SDL_Texture *sprites;

	Enemy(int x, int y);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	uint life;
	uint score;

	SDL_Texture *sprites = nullptr;


public:

	virtual void Move() {};
	virtual void Draw(SDL_Texture *sprites);
	virtual void OnCollision(Collider *collider);

};


#endif

