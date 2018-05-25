#ifndef MODULEENEMIES_H
#define MODULEENEMIES_H

#include "Module.h"
#include "p2Point.h"

//Include here Enemies modules

#define MAX_ENEMIES 1000

enum ENEMY_TYPES {

	NO_TYPE,
	ENEMY_WASP,
	ENEMY_RHINO,
	ENEMY_ZICZAC,
	ENEMY_LAMELLA,
	ENEMY_BEE,
	CARS
};

class Enemy;

struct EnemyInfo {

	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y;
	bool PowerUp;
	fPoint toGo;
};


class ModuleEnemies : public Module {

public:

	ModuleEnemies();
	~ModuleEnemies();
	SDL_Texture *sprites;
	SDL_Texture* carSprites;
	SDL_Texture* CommonEnemyes;

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp(); 

	void OnCollision(Collider *c1, Collider *c2);
	bool AddEnemy(ENEMY_TYPES type, int x, int y, bool PowerUp);
	bool SpawnEnemyCheat = false;

private:

	void SpawnEnemy(const EnemyInfo &info);

	EnemyInfo queue[MAX_ENEMIES];
	Enemy *enemies[MAX_ENEMIES];
	

};

#endif