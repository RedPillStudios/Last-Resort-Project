#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleTextures.h"
#include "ModuleParticles.h"
#include "ModuleSound.h"
#include "ModulePlayer.h"
#include "Enemy.h"
#include "EnemyRhino.h"
#include "EnemyWasp.h"
#include "EnemyZicZac.h"
#include "EnemySuicide.h"
#include "CarsToFast.h"
#include "ModuleSceneLvl1.h"

#define SPAWN_MARGIN 50

ModuleEnemies::ModuleEnemies() {

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies() {}

bool ModuleEnemies::Start() {

	LOG("Starting Module Enemies");
	return true;
}

bool ModuleEnemies::CleanUp() {

	LOG("Cleaning Up Enemies Module");

	for (uint i = 0; i < MAX_ENEMIES; ++i) {

		if (enemies[i] != nullptr) {
			App->textures->Unload(enemies[i]->sprites);
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

update_status ModuleEnemies::PreUpdate() {

	for (uint i = 0; i < MAX_ENEMIES; ++i) {

		if (queue[i].type != ENEMY_TYPES::NO_TYPE) {

			if (queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN) {
		
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
			}
		}
	}
	
	return UPDATE_CONTINUE;
}
update_status ModuleEnemies::Update() {

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Move();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Draw(enemies[i]->sprites);

	return UPDATE_CONTINUE;


}

update_status ModuleEnemies::PostUpdate() {

	//Check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i) {

		if (enemies[i] != nullptr) {

			  if (enemies[i]->position.x * SCREEN_SIZE < (App->scene1background->position_min_limit) - SPAWN_MARGIN) {
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}
	return UPDATE_CONTINUE;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y) {

	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i) {

		if (queue[i].type == ENEMY_TYPES::NO_TYPE) {

			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{
		case ENEMY_TYPES::ENEMY_RHINO:
			enemies[i] = new Enemy_Rhino(info.x, info.y);
			break;
    case ENEMY_TYPES::ENEMY_WASP:
	  	enemies[i] = new EnemyWasp(info.x, info.y);
	  	break;

	case ENEMY_TYPES::ENEMY_ZICZAC:
		enemies[i] = new EnemyZicZac(info.x, info.y);
		break;
	case ENEMY_TYPES::ENEMY_SUICIDE:
		enemies[i] = new EnemySuicide(info.x, info.y);
		break;
	case ENEMY_TYPES::CARS:
		enemies[i] = new CarsToFast(info.x, info.y);
		break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider *c1, Collider *c2) {
		
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		
 if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1) {

		//	enemies[i]->OnCollision(c2);
			--(enemies[i]->life);

			if (enemies[i]->life <= 0) {
				/*if (enemies[i]. == ENEMY_RHINO)     S HA DE POSAR IF ENEMY TYPE == ENEMY RHINO Y ASI
					App->player->PlayerScore += 300;
				else if (ENEMY_TYPES::ENEMY_ZICZAC)
					App->player->PlayerScore += 100;
				else if (ENEMY_TYPES::ENEMY_WASP)
					App->player->PlayerScore += 100;
				else if (ENEMY_TYPES::CARS)
					App->player->PlayerScore += 100;*/
				delete enemies[i];
				enemies[i] = nullptr;
				break;
			}
		} 
	}
}