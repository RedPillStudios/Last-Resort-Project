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

ModulePowerUp::ModulePowerUp() {

	Power_Up.PushBack({18,64,31,16});
	Power_Up.PushBack({ 49,64,31,16 });
	Power_Up.loop = true;
	Power_Up.speed = 0.05f;

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

	Charge.PushBack({0,0,47,47});
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

	powerup = App->textures->Load("Images/General/PowerUps_Sprite.png");
	PickUpSpeed = App->sound->LoadChunk("Audio/General/005_PowerUpSpeed.wav");
	PickUpWeapon = App->sound->LoadChunk("Audio/General/006_PowerUpWeapon.wav");
	HOU_Texture = App->textures->Load("Images/Player/Ship&Ball_Sprite.png");
	Charge_texture = App->textures->Load("Images/Player/Charge_Ball.png");

	HOU_activated = false;
	fixed = false;
	current_animation = &HOU_Front;

	Power_Up_animation = &Power_Up;
	colliderPowerUp = App->collision->AddCollider({ 500,120,31,16 }, COLLIDER_POWER_UP, this);
	colliderHUB = App->collision->AddCollider({ -2000,-200,22,16 },COLLIDER_HOU, this);

	return true;
}

bool ModulePowerUp::CleanUp() {

	LOG("Cleaning Up Power Ups");
	App->textures->Unload(powerup);
	return true;
}


update_status ModulePowerUp::Update() {

	if (HOU_activated == false) {
		App->render->Blit(powerup, 500, 120, &Power_Up_animation->GetCurrentFrame());
	}

	else if (HOU_activated == true) {
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) {
			current_animation = &HOU_Down;
			if (fixed==false) {
				HOU_position_x = App->player->position.x + 10;
				HOU_position_y = App->player->position.y + 15;
			}

		}
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) {
			current_animation = &HOU_Front;
			if (fixed == false) {
				HOU_position_x = App->player->position.x + 38;
				HOU_position_y = App->player->position.y - 2;
			}

		}
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) {
			current_animation = &HOU_Back;
			if (fixed == false) {
				HOU_position_x = App->player->position.x - 25;
				HOU_position_y = App->player->position.y - 2;
			}

		}
		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) {
			current_animation = &HOU_UP;
			if (fixed == false) {
				HOU_position_x = App->player->position.x + 10;
				HOU_position_y = App->player->position.y - 25;
			}

		}
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT) {
			Charge_animation = &Charge;
			App->render->Blit(Charge_texture, HOU_position_x-10, HOU_position_y-15, &Charge_animation->GetCurrentFrame());
		}
		else if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
			if (current_animation == &HOU_Front) {
				App->particles->HOU_Shot.Speed.x = 5;
				App->particles->HOU_Shot.Speed.y = 0;
				App->particles->AddParticle(App->particles->HOU_Shot, HOU_position_x+3, HOU_position_y, COLLIDER_PLAYER_SHOT);
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

		}
		colliderHUB->SetPos(HOU_position_x, HOU_position_y);
		HOU_position_x++; //automatic_movement
		App->render->Blit(HOU_Texture, HOU_position_x, HOU_position_y, &current_animation->GetCurrentFrame());
		if (App->input->keyboard[SDL_SCANCODE_C] == KEY_STATE::KEY_DOWN) {
			fixed = true;
		}
	
	}
		return UPDATE_CONTINUE;
	}

void ModulePowerUp::OnCollision(Collider *c1, Collider *c2) {

if (c1->type == COLLIDER_POWER_UP && c2->type == COLLIDER_PLAYER) {
		App->powerup->HOU_activated = true;
		App->powerup->colliderPowerUp->to_delete = true;
		HOU_position_x = App->player->position.x + 38;
		HOU_position_y = App->player->position.y - 2;
	}
if (c1->type == COLLIDER_POWER_UP && c2->type == COLLIDER_PLAYER) {

}
}