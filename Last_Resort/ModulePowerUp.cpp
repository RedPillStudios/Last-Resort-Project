#include "Application.h"
#include "ModulePowerUp.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleInput.h"
#include "Module_Hou_Player1.h"
#include "Module_Hou_Player2.h"
#include <math.h>

#define SPAWN_MARGIN 50

powerUp_Misiles::powerUp_Misiles(int x, int y) : powerUp(x, y) {

	powerUp::sprite = App->textures->Load("Images/General/PowerUps_Sprite.png");
	Blue.PushBack({ 49,64,31,16 });
	Red.PushBack({ 18,64,31,16 });
	collider = App->collision->AddCollider({ 500,120,31,16 }, COLLIDER_TYPE::COLLIDER_POWER_UP, (Module*)App->powerup);
	animation = &Red;
	type = POWERUP_TYPES::MISILES;

};

void powerUp_Misiles::Update() {
	
	timing++;
	if (timing >= 20) {
		if (animation == &Red) {
			ColorRed = false;
			ColorBlue = true;
			animation = &Blue;
		}
		else {
			ColorRed = true;
			ColorBlue = false;
			animation = &Red;
		}
		timing = 0;
	}
};

powerUp_Laser::powerUp_Laser(int x, int y) : powerUp(x, y) {

	powerUp::sprite = App->textures->Load("Images/General/PowerUps_Sprite.png");
	Blue.PushBack({ 49,80,31,16 });
	Red.PushBack({ 18,80,31,16 });
	collider = App->collision->AddCollider({ 500,120,31,16 }, COLLIDER_TYPE::COLLIDER_POWER_UP, (Module*)App->powerup);
	animation = &Red;
	
	type = POWERUP_TYPES::LASER;
};

void powerUp_Laser::Update() {

	timing++;
	if (timing >= 20) {
		if (animation == &Red) {
			ColorRed = false;
			ColorBlue = true;
			animation = &Blue;
		}
		else {
			ColorRed = true;
			ColorBlue = false;
			animation = &Red;
		}
		timing = 0;
	}

};

ModulePowerUp::ModulePowerUp() {

	for (uint i = 0; i < MAX_POWERUP; ++i)
		PowerUps[i] = nullptr;
}

ModulePowerUp::~ModulePowerUp() {}

bool ModulePowerUp::Start() {

	LOG("Loading PowerUps");
	if (App->player->IsEnabled() == true && App->powerup->IsEnabled() == false)
		App->powerup->Enable();

	PickUpSpeed = App->sound->LoadChunk("Audio/General/005_PowerUpSpeed.wav");
	PickUpWeapon = App->sound->LoadChunk("Audio/General/006_PowerUpWeapon.wav");


	return true;
}

bool ModulePowerUp::CleanUp() {

	LOG("Cleaning Up Power Ups");
	for (uint i = 0; i < MAX_POWERUP; ++i) {
		if (PowerUps[i] != nullptr) {
			App->textures->Unload(PowerUps[i]->sprite);
			PowerUps[i]->collider->to_delete = true;
			PowerUps[i]->animation = nullptr;

			delete PowerUps[i];
			PowerUps[i] = nullptr;
			
		}

		queue[i].type = NON;

	}


	App->sound->UnloadChunks(PickUpSpeed);
	App->sound->UnloadChunks(PickUpWeapon);


	return true;
}


update_status ModulePowerUp::PreUpdate() {

	for (uint i = 0; i < MAX_POWERUP; ++i) {

		if (queue[i].type != POWERUP_TYPES::NON) {

			if (queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN) {
				spawnPowerUp(queue[i]);
				queue[i].type = POWERUP_TYPES::NON;
				LOG("Spawning powerUp at %d", queue[i].x * SCREEN_SIZE);
			}
		}
	}

	return UPDATE_CONTINUE;
}


update_status ModulePowerUp::Update() {

	for (uint i = 0; i < MAX_POWERUP; ++i)
		if (PowerUps[i] != nullptr) PowerUps[i]->Update();
	for (uint i = 0; i < MAX_POWERUP; ++i)
		if (PowerUps[i] != nullptr)PowerUps[i]->Draw(PowerUps[i]->sprite);

	return UPDATE_CONTINUE;
}

void ModulePowerUp::OnCollision(Collider *c1, Collider *c2) {

	for (uint i = 0; i < MAX_POWERUP; ++i) {
		if(c2->type == COLLIDER_PLAYER){
		if (PowerUps[i] != nullptr && PowerUps[i]->GetCollider() == c1) {
		
			PowerUps[i]->OnCollision(c2);
			if (c2->type == COLLIDER_PLAYER) {
				App->HOU_Player1->HOU_activated = true;
				if (PowerUps[i]->ColorBlue==true) {
					App->HOU_Player1->Blue = true;
					App->HOU_Player1->Red = false;
				}
				else if (PowerUps[i]->ColorRed==true) {
					App->HOU_Player1->Blue = false;
					App->HOU_Player1->Red = true;
				}
				if (PowerUps[i]->type == POWERUP_TYPES::MISILES)
					App->player->WeaponType = 3;
				if (PowerUps[i]->type == POWERUP_TYPES::LASER)
					App->player->WeaponType = 1;
			}
			if (c2->type == COLLIDER_PLAYER2) {
				App->HOU_Player2->HOU_activated = true;
				if (PowerUps[i]->type == POWERUP_TYPES::MISILES)
					App->player2->WeaponTypeP2 = 3;
				if (PowerUps[i]->type == POWERUP_TYPES::LASER)
					App->player2->WeaponTypeP2 = 1;
			}
			//ADD HERE App.player.score += score;
			delete PowerUps[i];
			PowerUps[i] = nullptr;
			break;
		}
		
	}
}

bool ModulePowerUp::AddPowerUp(POWERUP_TYPES type, int x, int y) {

	bool ret = false;

	for (uint i = 0; i < MAX_POWERUP; ++i) {

		if (queue[i].type == POWERUP_TYPES::NON) {

			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModulePowerUp::spawnPowerUp(const PowerUpInfo &info)
{
	// find room for the new enemy
	uint i = 0;
	for (; PowerUps[i] != nullptr && i < MAX_POWERUP; ++i);

	if (i != MAX_POWERUP)
	{
		switch (info.type)	{
        
		case POWERUP_TYPES::MISILES:
			PowerUps[i] = new powerUp_Misiles(info.x, info.y);
			break;
		case POWERUP_TYPES::LASER:
			PowerUps[i] = new powerUp_Laser(info.x, info.y);
			break;
		}
	}
}
