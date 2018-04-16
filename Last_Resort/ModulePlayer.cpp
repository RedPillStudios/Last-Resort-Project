#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleSound.h"
#include "ModuleFadeToBlack.h"
#include "ModulePowerUp.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{

	position.x = 20;
	position.y = SCREEN_HEIGHT/2;

	Standard.PushBack({64,0,32,12});

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

	DestroyShip.speed = 0.3f;
	DestroyShip.loop = false;
	

}

ModulePlayer::~ModulePlayer() {}

// Load assets
bool ModulePlayer::Start() {

	LOG("Loading player 2 textures");
	
	if (App->particles->IsEnabled() == false)
		App->particles->Enable();

	if (IsEnabled()) {
		App->collision->Enable();
		App->powerup->Enable();
	}
	if (App->player2->IsEnabled() == true)
		App->player2->Disable();
	
	graphics = App->textures->Load("Images/Player/Ship&Ball_Sprite.png"); // arcade version
	Shot_Sound = App->sound->LoadChunk("Audio/Shot_Sound.wav");
	Ship1Collider = App->collision->AddCollider({ 64,0,32,12 }, COLLIDER_PLAYER, this);

	AppearAnim = true;
	Dead = false;

	current_animation = &Appear;

	return true;
}

bool ModulePlayer::CleanUp() {

	LOG("Cleaning Up Player 1 Module");
	App->collision->Disable();
	App->powerup->Disable();
	current_animation = NULL;
	//App->particles->Disable();
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModulePlayer::Update() {
	
	if (current_animation == &Appear) {
		position.x = -12;
		if (Appear.Finished()) {
			resetPosition();
			current_animation = &Standard;
		}
	}

	
		////Appear/Disappear player 2
		//if (App->input->keyboard[SDL_SCANCODE_6] == KEY_STATE::KEY_DOWN && pressed == false) {
		//	pressed = true;
		//	Dead = false;
		//	App->player2->Enable();
		//	App->player2->resetPosition2();

		//}

		//else if (App->input->keyboard[SDL_SCANCODE_6] == KEY_STATE::KEY_DOWN && pressed == true) {
		//	App->player2->Ship2Collider->to_delete = true;
		//	pressed = false;
		//	App->player2->Disable();
		//}

		
		int speed = 3;

		if (current_animation != &DestroyShip && Appear.Finished()) {
			current_animation = &Standard;
		}
		if (!Dead&& current_animation != &Appear) {
			//Movement Up
			if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) {
				current_animation = &Up;
				position.y -= speed;
				while (position.y <= 2) {
					position.y = 2;
					break;
				}
			}
			//Movement Down
			if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) {
				current_animation = &Down;
				position.y += speed;
				while (position.y >= SCREEN_HEIGHT - 15) {
					position.y = SCREEN_HEIGHT - 15;
					break;
				}
			}
			//Movement Right
			if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) {
				position.x += speed;
				while (position.x >= SCREEN_WIDTH - 30) {
					position.x = SCREEN_WIDTH - 30;
					break;
				}
			}
			//Movement left
			if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) {
				position.x -= speed;
				while (position.x <= 2) {
					position.x = 2;
					break;
				}
			}
			//Shoot
			if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {

				App->particles->AddParticle(App->particles->Laser, setFirePos().x, setFirePos().y);
				App->particles->AddParticle(App->particles->ShootExplosion, setFirePos().x, setFirePos().y);
				Mix_PlayChannel(-1, Shot_Sound, 0);
			}
		}

	// Draw everything --------------------------------------
		if (current_animation == &Appear) {
			App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
		}
		else if (current_animation == &DestroyShip) {
			App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
		}
		else {
			App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()), 0.0f);
		}

	Ship1Collider->SetPos(position.x, position.y);
	
	
	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider *c1, Collider *c2) {
	if (((c1->type == COLLIDER_TYPE::COLLIDER_ENEMY || c1->type == COLLIDER_TYPE::COLLIDER_WALL) && c2->type == COLLIDER_PLAYER) || ((c2->type == COLLIDER_TYPE::COLLIDER_ENEMY || c2->type == COLLIDER_TYPE::COLLIDER_WALL) && c1->type == COLLIDER_PLAYER)) {

		Dead = true;
		current_animation = &DestroyShip;
		Ship1Collider->to_delete = true;

		if (DestroyShip.Finished()) {
		App->player->Disable();
		}

		if (App->player2->IsEnabled()==false) {
			App->fade->FadeToBlack((Module*)App->scene1background, (Module*)App->gameover, 1.0f);
		}


	}
}