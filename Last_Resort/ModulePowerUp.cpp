#include "Application.h"
#include "ModulePowerUp.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleInput.h"

#define SPAWN_MARGIN 50

powerUp_red::powerUp_red(int x, int y) : powerUp(x, y) {

	powerUp::sprite = App->textures->Load("Images/General/PowerUps_Sprite.png");
	Red.PushBack({ 49,64,31,16 });
	Red.PushBack({ 18,64,31,16 });
	collider = App->collision->AddCollider({ 500,120,31,16 }, COLLIDER_TYPE::COLLIDER_POWER_UP, (Module*)App->powerup);
	animation = &Red;
	Red.speed = 0.1f;
	type = POWERUP_TYPES::RED;

};

powerUp_Laser::powerUp_Laser(int x, int y) : powerUp(x, y) {

	powerUp::sprite = App->textures->Load("Images/General/PowerUps_Sprite.png");
	ChangeColor.PushBack({ 49,80,31,16 });
	ChangeColor.PushBack({ 18,80,31,16 });
	collider = App->collision->AddCollider({ 500,120,31,16 }, COLLIDER_TYPE::COLLIDER_POWER_UP, (Module*)App->powerup);
	animation = &ChangeColor;
	ChangeColor.speed = 0.1f;
	type = POWERUP_TYPES::LASER;
};


ModulePowerUp::ModulePowerUp() {

	for (uint i = 0; i < MAX_POWERUP; ++i)
		PowerUps[i] = nullptr;
	int counter = 0;
	for (uint i = 0; i <= 7; ++i) {
		HOU_Front_Up.PushBack({ 240,counter,21,21 });
		counter += 21;
		if (counter >= 168)
			counter = 0;
	}

	HOU_Front_Up.speed = 0.4f;

	for (uint i = 0; i < 7; i++) {
		HOU_Front_Down.PushBack({ 469,counter,21,21 });
		counter += 21;
		if (counter >= 168)
			counter = 0;
	}
	HOU_Front_Down.speed = 0.4f;

	for (uint i = 0; i < 7; i++) {
		HOU_Back_Down.PushBack({ 398,counter,21,21 });
		counter += 21;
		if (counter >= 168)
			counter = 0;
	}
	HOU_Back_Down.speed = 0.4f;


	for (uint i = 0; i < 7; i++) {
		HOU_Back_UP.PushBack({ 311,counter,21,21 });
		counter += 21;
		if (counter >= 168)
			counter = 0;
	}
	HOU_Back_UP.speed = 0.4f;

	HOU_Front.PushBack({ 195,0,22,16 });
	HOU_Front.PushBack({ 195,16,22,16 });
	HOU_Front.PushBack({ 195,32,22,16 });
	HOU_Front.PushBack({ 195,48,22,16 });
	HOU_Front.PushBack({ 195,64,22,16 });
	HOU_Front.PushBack({ 195,80,22,16 });
	HOU_Front.PushBack({ 195,96,22,16 });
	HOU_Front.PushBack({ 195,112,22,16 });
	HOU_Front.loop = true;
	HOU_Front.speed = 0.4f;

	HOU_Back.PushBack({ 354,0,22,16 });
	HOU_Back.PushBack({ 354,16,22,16 });
	HOU_Back.PushBack({ 354,32,22,16 });
	HOU_Back.PushBack({ 354,48,22,16 });
	HOU_Back.PushBack({ 354,64,22,16 });
	HOU_Back.PushBack({ 354,80,22,16 });
	HOU_Back.PushBack({ 354,96,22,16 });
	HOU_Back.PushBack({ 354,112,22,16 });
	HOU_Back.loop = true;
	HOU_Back.speed = 0.4f;

	HOU_UP.PushBack({ 278,0,16,22 });
	HOU_UP.PushBack({ 278,22,16,22 });
	HOU_UP.PushBack({ 278,44,16,22 });
	HOU_UP.PushBack({ 278,66,16,22 });
	HOU_UP.PushBack({ 278,88,16,22 });
	HOU_UP.PushBack({ 278,110,16,22 });
	HOU_UP.PushBack({ 278,132,16,22 });
	HOU_UP.PushBack({ 278,154,16,22 });
	HOU_UP.loop = true;
	HOU_UP.speed = 0.4f;

	HOU_Down.PushBack({ 436,0,16,22 });
	HOU_Down.PushBack({ 436,22,16,22 });
	HOU_Down.PushBack({ 436,44,16,22 });
	HOU_Down.PushBack({ 436,66,16,22 });
	HOU_Down.PushBack({ 436,88,16,22 });
	HOU_Down.PushBack({ 436,110,16,22 });
	HOU_Down.PushBack({ 436,132,16,22 });
	HOU_Down.PushBack({ 436,154,16,22 });
	HOU_Down.loop = true;
	HOU_Down.speed = 0.4f;

	Charge.PushBack({ 0,0,47,47 });
	Charge.PushBack({ 47,0,47,47 });
	Charge.PushBack({ 94,0,47,47 });
	Charge.PushBack({ 141,0,47,47 });
	Charge.PushBack({ 188,0,47,47 });
	Charge.PushBack({ 0,47,47,47 });
	Charge.PushBack({ 47,47,47,47 });
	Charge.PushBack({ 94,47,47,47 });
	Charge.PushBack({ 141,47,47,47 });
	Charge.PushBack({ 188,47,47,47 });
	Charge.PushBack({ 0,94,47,47 });
	Charge.PushBack({ 47,94,47,47 });
	Charge.PushBack({ 94,94,47,47 });
	Charge.PushBack({ 141,94,47,47 });
	Charge.PushBack({ 188,94,47,47 });

	Charge.loop = true;
	Charge.speed = 0.4f;

}

ModulePowerUp::~ModulePowerUp() {}

bool ModulePowerUp::Start() {

	LOG("Loading PowerUps");
	if (App->player->IsEnabled() == true && App->powerup->IsEnabled() == false)
		App->powerup->Enable();

	PickUpSpeed = App->sound->LoadChunk("Audio/General/005_PowerUpSpeed.wav");
	PickUpWeapon = App->sound->LoadChunk("Audio/General/006_PowerUpWeapon.wav");
	HOU_Texture = App->textures->Load("Images/Player/Ship&Ball_Sprite.png");
	Charge_texture = App->textures->Load("Images/Player/Charge_Ball.png");

	HOU_activated = false;
	fixed = false;

	current_animation = &HOU_Front;

	colliderHUB = App->collision->AddCollider({ -2000,-200,22,16 }, COLLIDER_HOU, this);

	AddPowerUp(RED, 600, 16);
	AddPowerUp(RED, 400, 16);
	AddPowerUp(LASER, 400, 90);
	return true;
}

bool ModulePowerUp::CleanUp() {

	LOG("Cleaning Up Power Ups");
	App->textures->Unload(HOU_Texture);
	App->textures->Unload(Charge_texture);
	return true;
}


update_status ModulePowerUp::PreUpdate() {

	for (uint i = 0; i < MAX_POWERUP; ++i) {

		if (queue[i].type != POWERUP_TYPES::NON) {

			if (queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN) {

				spawnPowerUp(queue[i]);
				queue[i].type = POWERUP_TYPES::NON;
				LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
			}
		}
	}

	return UPDATE_CONTINUE;
}


update_status ModulePowerUp::Update() {


	for (uint i = 0; i < MAX_POWERUP; ++i)
		if (PowerUps[i] != nullptr)PowerUps[i]->Draw(PowerUps[i]->sprite);

	if (HOU_activated == true) {
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) {
			current_animation = &HOU_Down;
			HOU_position_x = App->player->position.x + 10;
			HOU_position_y = App->player->position.y + 15;

		}
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) {
			current_animation = &HOU_Front;
			HOU_position_x = App->player->position.x + 38;
			HOU_position_y = App->player->position.y - 2;


		}
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) {
			current_animation = &HOU_Back;
			HOU_position_x = App->player->position.x - 25;
			HOU_position_y = App->player->position.y - 2;
		}
		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) {
			current_animation = &HOU_UP;
			HOU_position_x = App->player->position.x + 10;
			HOU_position_y = App->player->position.y - 25;
		}
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) {
			current_animation = &HOU_Front_Up;
			HOU_position_x = App->player->position.x + 38;
			HOU_position_y = App->player->position.y - 25;
		}
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) {
			current_animation = &HOU_Front_Down;
			HOU_position_x = App->player->position.x + 38;
			HOU_position_y = App->player->position.y + 15;
		}
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) {
			current_animation = &HOU_Back_Down;
			HOU_position_x = App->player->position.x - 25;
			HOU_position_y = App->player->position.y + 15;
		}
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) {
			current_animation = &HOU_Back_UP;
			HOU_position_x = App->player->position.x - 25;
			HOU_position_y = App->player->position.y - 25;
		}





		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT) {
			Charge_animation = &Charge;
			App->render->Blit(Charge_texture, HOU_position_x - 10, HOU_position_y - 15, &Charge_animation->GetCurrentFrame());
		}
		else if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
			if (current_animation == &HOU_Front) {
				App->particles->HOU_Shot.Speed.x = 5;
				App->particles->HOU_Shot.Speed.y = 0;
				App->particles->AddParticle(App->particles->HOU_Shot, HOU_position_x + 3, HOU_position_y, COLLIDER_PLAYER_SHOT);
			}
			if (current_animation == &HOU_UP) {
				App->particles->HOU_Shot.Speed.x = 1;
				App->particles->HOU_Shot.Speed.y = -5;
				App->particles->AddParticle(App->particles->HOU_Shot, HOU_position_x, HOU_position_y, COLLIDER_PLAYER_SHOT);
			}
			if (current_animation == &HOU_Down) {
				App->particles->HOU_Shot.Speed.x = 1;
				App->particles->HOU_Shot.Speed.y = 5;
				App->particles->AddParticle(App->particles->HOU_Shot, HOU_position_x, HOU_position_y, COLLIDER_PLAYER_SHOT);
			}
			if (current_animation == &HOU_Back) {
				App->particles->HOU_Shot.Speed.x = -5;
				App->particles->HOU_Shot.Speed.y = 0;
				App->particles->AddParticle(App->particles->HOU_Shot, HOU_position_x - 3, HOU_position_y, COLLIDER_PLAYER_SHOT);
			}
			if (current_animation == &HOU_Front_Up) {
				App->particles->HOU_Shot.Speed.x = 5;
				App->particles->HOU_Shot.Speed.y = -5;
				App->particles->AddParticle(App->particles->HOU_Shot, HOU_position_x - 3, HOU_position_y, COLLIDER_PLAYER_SHOT);
			}
			if (current_animation == &HOU_Front_Down) {
				App->particles->HOU_Shot.Speed.x = 5;
				App->particles->HOU_Shot.Speed.y = 5;
				App->particles->AddParticle(App->particles->HOU_Shot, HOU_position_x - 3, HOU_position_y, COLLIDER_PLAYER_SHOT);
			}
			if (current_animation == &HOU_Back_UP) {
				App->particles->HOU_Shot.Speed.x = -5;
				App->particles->HOU_Shot.Speed.y = -5;
				App->particles->AddParticle(App->particles->HOU_Shot, HOU_position_x - 3, HOU_position_y, COLLIDER_PLAYER_SHOT);
			}
			if (current_animation == &HOU_Back_Down) {
				App->particles->HOU_Shot.Speed.x = -5;
				App->particles->HOU_Shot.Speed.y = 5;
				App->particles->AddParticle(App->particles->HOU_Shot, HOU_position_x - 3, HOU_position_y, COLLIDER_PLAYER_SHOT);
			}

		}
		colliderHUB->SetPos(HOU_position_x, HOU_position_y);
		HOU_position_x++; //automatic_movement
		App->render->Blit(HOU_Texture, HOU_position_x, HOU_position_y, &current_animation->GetCurrentFrame());

	}
	return UPDATE_CONTINUE;
}

void ModulePowerUp::OnCollision(Collider *c1, Collider *c2) {

	for (uint i = 0; i < MAX_POWERUP; ++i) {

		if (PowerUps[i] != nullptr && PowerUps[i]->GetCollider() == c1) {
			HOU_activated = true;
			PowerUps[i]->OnCollision(c2);
			if (PowerUps[i]->type == POWERUP_TYPES::RED)
				App->player->WeaponType = 2;
			if (PowerUps[i]->type == POWERUP_TYPES::LASER)
				App->player->WeaponType = 1;
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
		switch (info.type)
		{
		case POWERUP_TYPES::RED:
			PowerUps[i] = new powerUp_red(info.x, info.y);
			break;
		case POWERUP_TYPES::LASER:
			PowerUps[i] = new powerUp_Laser(info.x, info.y);
			break;
		}
	}
}