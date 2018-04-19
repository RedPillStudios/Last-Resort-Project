#ifndef MODULEENEMIES_H
#define MODULEENEMIES_H

#include "Module.h"

//Include here Enemies modules

#define MAX_ENEMIES 100

enum ENEMY_TYPES {

	NO_TYPE,
	ENEMY_WASP,
	ENEMY_RHINO,
	ENEMY_ZICZAC,
	ENEMY_SUICIDE,
	CARS
};

class Enemy;

struct EnemyInfo {

	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y;
	
};


class ModuleEnemies : public Module {

public:

	ModuleEnemies();
	~ModuleEnemies();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp(); 

	void OnCollision(Collider *c1, Collider *c2);
	bool AddEnemy(ENEMY_TYPES type, int x, int y);
	bool SpawnEnemyCheat = false;

private:

	void SpawnEnemy(const EnemyInfo &info);

	EnemyInfo queue[MAX_ENEMIES];
	Enemy *enemies[MAX_ENEMIES];
	

};

#endif