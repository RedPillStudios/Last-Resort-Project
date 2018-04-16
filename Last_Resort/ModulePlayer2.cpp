#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleSound.h"
#include "ModuleFadeToBlack.h"
#include "ModulePowerUp.h"
#include "ModulePlayer2.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA


ModulePlayer2::ModulePlayer2()
{

	positionp2.x = 20;
	positionp2.y = SCREEN_HEIGHT / 4;

	Standard.PushBack({ 64,0,32,12 });

	Up.PushBack({ 32,0,32,13 });
	Up.PushBack({ 0,0,32,13 });
	Up.speed = 0.10f;
	Up.loop = false;

	Down.PushBack({ 96,0,32,12 });
	Down.PushBack({ 128,1,32,11 });
	Down.speed = 0.10f;
	Down.loop = false;

	Appear.PushBack({ 0,135,64,25 });
	Appear.PushBack({ 0,160,64,25 });
	Appear.PushBack({ 0,185,64,25 });
	Appear.PushBack({ 0,210,64,25 });
	Appear.PushBack({ 64,135,64,25 });
	Appear.PushBack({ 64,160,64,25 });
	Appear.PushBack({ 64,185,64,25 });
	Appear.PushBack({ 64,210,64,25 });
	Appear.PushBack({ 128,139,64,19 });
	Appear.PushBack({ 128,158,64,19 });
	Appear.speed = 0.2f;
	Appear.loop = false;

	DestroyShip.PushBack({ 0,16,55,17 });
	DestroyShip.PushBack({ 0,33,55,17 });
	DestroyShip.PushBack({ 0,50,55,17 });
	DestroyShip.PushBack({ 0,67,55,17 });
	DestroyShip.PushBack({ 0,84,55,17 });
	DestroyShip.PushBack({ 0,101,55,17 });
	DestroyShip.PushBack({ 55,16,55,17 });
	DestroyShip.PushBack({ 55,33,55,17 });
	DestroyShip.PushBack({ 55,50,55,17 });
	DestroyShip.PushBack({ 55,67,55,17 });
	DestroyShip.PushBack({ 55,84,55,17 });
	DestroyShip.PushBack({ 55,101,55,17 });

	DestroyShip.PushBack({ 110,16,55,17 });
	DestroyShip.PushBack({ 110,33,55,17 });
	DestroyShip.PushBack({ 110,50,55,17 });
	DestroyShip.PushBack({ 110,67,55,17 });
	DestroyShip.PushBack({ 110,84,55,17 });
	DestroyShip.PushBack({ 110,101,55,17 });
	DestroyShip.PushBack({ 178,122,2,2 });

	DestroyShip.speed = 0.3f;
	DestroyShip.loop = false;
}

ModulePlayer2::~ModulePlayer2() {}

// Load assets
bool ModulePlayer2::Start() {

	if (IsEnabled()) {

		if (App->particles->IsEnabled() == false)
			App->particles->Enable();
		if (App->collision->IsEnabled() == false) {
			App->collision->Enable();
		}
		if (App->powerup->IsEnabled() == false) {
			App->powerup->Enable();
		}
	}
	LOG("Loading player textures");

	graphicsp2 = App->textures->Load("Images/Player/Ship&Ball_Sprite.png"); // arcade version
	Shot_Sound = App->sound->LoadChunk("Audio/Shot_Sound.wav");
	Ship2Collider = App->collision->AddCollider({ 64,0,32,12 }, COLLIDER_PLAYER, this);
	
	AppearAnim = true;
	Dead = false;

	Appear.Reset();
	DestroyShip.Reset();

	current_animation2 = &Appear;

	return true;
}

bool ModulePlayer2::CleanUp() {

	LOG("Cleaning Up Player 2 Module")
	App->textures->Unload(graphicsp2);
	current_animation2=NULL;
	Ship2Collider = NULL;
	//App->powerup->Disable();
	return true;
}

// Update: draw background
update_status ModulePlayer2::Update() {
	
	int speed = 3;

	if (current_animation2 == &Appear) {
		positionp2.x = -12;
		if (Appear.Finished()) {
			resetPosition2();
			current_animation2 = &Standard;
		}
	}


		if (current_animation2 != &DestroyShip && Appear.Finished()) {
			current_animation2 = &Standard;
		}


		if (!Dead&& current_animation2 != &Appear) {
		//Movement Up
		if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT) {
			current_animation2 = &Up;
			positionp2.y -= speed;
			while (positionp2.y <= 2) {
				positionp2.y = 2;
				break;
			}
		}
		/*Movement Down*/
		if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT) {
			current_animation2 = &Down;
			positionp2.y += speed;
			while (positionp2.y >= SCREEN_HEIGHT - 15) {
				positionp2.y = SCREEN_HEIGHT - 15;
				break;
			}
		}
		/*Movement Right*/
		if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT) {
			positionp2.x += speed;
			while (positionp2.x >= SCREEN_WIDTH - 30) {
				positionp2.x = SCREEN_WIDTH - 30;
				break;
			}
		}
		/*Movement left*/
		if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT) {
			positionp2.x -= speed;
			while (positionp2.x <= 2) {
				positionp2.x = 2;
				break;
			}
		}
		/*Shoot*/
		if (App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_DOWN) {

			App->particles->AddParticle(App->particles->Laser, setFirePos2().x, setFirePos2().y,COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->ShootExplosion, setFirePos2().x, setFirePos2().y);
			Mix_PlayChannel(-1, Shot_Sound, 0);
		}
	}

	/* Draw everything --------------------------------------*/

		if (current_animation2 == &Appear) {
			App->render->Blit(graphicsp2, positionp2.x, positionp2.y, &(current_animation2->GetCurrentFrame()));
		}
		else if (current_animation2 == &DestroyShip) {
			App->render->Blit(graphicsp2, positionp2.x, positionp2.y, &(current_animation2->GetCurrentFrame()));
		}
		else {
			App->render->Blit(graphicsp2, positionp2.x, positionp2.y, &(current_animation2->GetCurrentFrame()), 0.0f);
		}

	Ship2Collider->SetPos(positionp2.x, positionp2.y);


	return UPDATE_CONTINUE;
}

void ModulePlayer2::OnCollision(Collider *c1, Collider *c2) {

	if (((c1->type == COLLIDER_TYPE::COLLIDER_ENEMY || c1->type == COLLIDER_TYPE::COLLIDER_WALL) && c2->type == COLLIDER_PLAYER) || ((c2->type == COLLIDER_TYPE::COLLIDER_ENEMY || c2->type == COLLIDER_TYPE::COLLIDER_WALL) && c1->type == COLLIDER_PLAYER)) {

		Dead = true;
		current_animation2 = &DestroyShip;
		Ship2Collider->to_delete = true;

		if (DestroyShip.Finished()) {
			Disable();
		}

	}
}