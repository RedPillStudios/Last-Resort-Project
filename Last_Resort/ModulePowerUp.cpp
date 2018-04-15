#include "Application.h"
#include "ModulePowerUp.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleInput.h"


ModulePowerUp::ModulePowerUp() {

	Anim.PushBack({ 18, 80, 31, 16 });
	Anim.PushBack({ 49, 80, 31, 16 });
	Anim.loop = true;
	Anim.speed = 0.1f;
}


ModulePowerUp::~ModulePowerUp() {}

bool ModulePowerUp::Start() {

	LOG("Loading PowerUps");
	if (App->player->IsEnabled() == true && App->powerup->IsEnabled() == false)
		App->powerup->Enable();

	powerup = App->textures->Load("Images/General/PoweUps_Sprite.png");
	PickUpSpeed = App->sound->LoadChunk("Audio/General/005_PowerUpSpeed.wav");
	PickUpWeapon = App->sound->LoadChunk("Audio/General/006_PowerUpWeapon.wav");

	colliderWeapon = App->collision->AddCollider({ 18, 80, 31, 16 }, COLLIDER_PLAYER, this);
	colliderSpeed = App->collision->AddCollider({ 0, 64, 18, 21 }, COLLIDER_PLAYER, this);

	return true;
}

bool ModulePowerUp::CleanUp() {

	LOG("Cleaning Up Power Ups");
	App->textures->Unload(powerup);
	return true;
}

update_status ModulePowerUp::Update() {
	
	Power_Up_Weapon = Anim.GetCurrentFrame();

	colliderSpeed->SetPos(Power_Up_Speed.x, Power_Up_Speed.y);
	colliderWeapon->SetPos(Power_Up_Weapon.x, Power_Up_Weapon.y);
	PowerUpAppear();

	return UPDATE_CONTINUE;
}

void ModulePowerUp::PowerUpAppear() {

	if (App->particles->Enemies_Speed >= ENEMIES_SPEED) {

		App->render->Blit(powerup, SCREEN_WIDTH - 1, SCREEN_HEIGHT / 2, &Power_Up_Speed);
		App->particles->Enemies_Speed = 0;
	}
	else if (App->input->keyboard[SDL_SCANCODE_8])
		App->render->Blit(powerup, SCREEN_WIDTH - 1, SCREEN_HEIGHT / 2, &Power_Up_Speed);

	if (App->particles->Enemies_Weapon >= ENEMIES_WEAPON) {

		App->render->Blit(powerup, SCREEN_WIDTH - 1, SCREEN_HEIGHT / 2, &Power_Up_Weapon);
		App->particles->Enemies_Weapon = 0;
	}
	else if (App->input->keyboard[SDL_SCANCODE_9])
		App->render->Blit(powerup, SCREEN_WIDTH - 1, SCREEN_HEIGHT / 2, &Power_Up_Weapon);
}


void ModulePowerUp::IsPicked(Collider *c1, Collider *c2) {

	if (c1->type == COLLIDER_TYPE::COLLIDER_PLAYER && c2 == colliderSpeed) {

		
	}
	else if (c1->type == COLLIDER_TYPE::COLLIDER_PLAYER && c2 == colliderWeapon) {


	}
}