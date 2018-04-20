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
#include "ModuleFonts.h"
#include "ModuleEnemies.h"
#include "ModuleSceneLvl1.h"

#include <stdio.h>

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA
ModulePlayer::ModulePlayer()
{

	Standard.PushBack({64,0,32,12});
	
	Up.PushBack({ 32,0,32,13 });
	Up.PushBack({ 0,0,32,13 });
	

	Up.speed = 0.2f;
	Up.loop = false;

	Down.PushBack({ 96,0,32,12 });
	Down.PushBack({ 128,1,32,11 });
	Down.speed = 0.2f;
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
	DestroyShip.PushBack({178,122,2,2});

	DestroyShip.speed = 0.3f;
	DestroyShip.loop = false;
}

ModulePlayer::~ModulePlayer() {}

// Load assets
bool ModulePlayer::Start() {

	LOG("Loading player 1 textures");
	position.x = App->scene1background->position_min_limit + 20;
	position.y = SCREEN_HEIGHT / 2;

	
	Appear.Reset();
	DestroyShip.Reset();
	graphicsp1 = App->textures->Load("Images/Player/Ship&Ball_Sprite.png");

	//font_score = App->fonts->Load("Images/Fonts/chars_Sprite1.png", "0123456789[]ABCDEFGHIJKLMNOPQRSTUVWXYZ_.&#", 3);

	Shot_Sound = App->sound->LoadChunk("Audio/Shot_Sound.wav");
	Ship1Collider = App->collision->AddCollider({ position.x, position.y,32,12 }, COLLIDER_PLAYER, this);

	ToBeDeleted = false;
	
	Dead = false;
	//Player1Activated = false;
	current_animation = &Appear;

	return true;
}

bool ModulePlayer::CleanUp() {

	LOG("Cleaning Up Player 1 Module");

	
	//App->powerup->Disable();
	current_animation =nullptr;
	//App->particles->Disable();

	
	//App->fonts->UnLoad(font_score);
	
	if (Ship1Collider != nullptr)
		Ship1Collider->to_delete = true; 

	App->sound->UnloadChunks(Shot_Sound);
	App->textures->Unload(graphicsp1);

	if (GOD) {
		GOD = !GOD;
	}

	//DestroyShip.Reset();
	return true;
}

// Update: draw background
update_status ModulePlayer::Update() {
	
	position.x += 1;
	

	int speed = 2;

	if (current_animation == &Appear) {
		position.x=App->scene1background->position_min_limit+2;
		
		if (Appear.Finished() && current_animation!=&Standard) {
			position.x = App->scene1background->position_min_limit + 32;
			current_animation = &Standard;
		}
	}
		if (current_animation != &DestroyShip && Appear.Finished()&& (current_animation != &Up )) {
			current_animation = &Standard;
		}

		if (!Dead&& current_animation != &Appear) {
			//Movement Up
			if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) {
				//current_animation = &Up;
				if (current_animation != &Up)
				{
					Up.Reset();
					current_animation = &Up;
				}
				//current_animation = &Up;
				position.y -= speed;
				while (position.y <= 2) {
					position.y = 2;
					break;
				}
			}
			else { current_animation = &Standard; }
			//Movement Down
			if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) {
				if (current_animation != &Down)
				{
					Down.Reset();
					current_animation = &Down;
				}
					
				position.y += speed;
				while (position.y >= SCREEN_HEIGHT - 15) {
					position.y = SCREEN_HEIGHT - 15;
					break;
				}
			}
			/*else {
				current_animation = &Standard;
			}*/
			//Movement Right
			if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) {
				position.x += speed;
				while (position.x >= App->scene1background->position_max_limit-32){
					position.x = App->scene1background->position_max_limit-32;
					break;
				}
			}
			//Movement left
			if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) {
				position.x -= speed;
				while (position.x <= App->scene1background->position_min_limit+1) {
					position.x = App->scene1background->position_min_limit+1;
					break;
				}
			}

			if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) {
				
				GOD = !GOD;
			}
			

			if (App->input->keyboard[SDL_SCANCODE_F11]==KEY_STATE::KEY_DOWN) {
				LOG("Spawning Enemie")
				  App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_ZICZAC, (App->player->position.x) + 200, App->player->position.y);
			}

			//Shoot
			if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
				App->particles->AddParticle(App->particles->Laser, setFirePos().x, setFirePos().y, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->ShootExplosion, setFirePos().x, setFirePos().y);
			
				Mix_PlayChannel(-1, Shot_Sound, 0);
			}
		}
		
		Ship1Collider->SetPos(position.x, position.y);
	// Draw everything --------------------------------------
		if (current_animation == &Appear) 
			App->render->Blit(graphicsp1, position.x, position.y, &(current_animation->GetCurrentFrame()));
		else if (current_animation == &DestroyShip)
			App->render->Blit(graphicsp1, position.x, position.y, &(current_animation->GetCurrentFrame()));
		else 
			App->render->Blit(graphicsp1, position.x, position.y, &(current_animation->GetCurrentFrame()));
	
		//sprintf_s(score_text, 10, "%7d", PlayerScore);
		//App->fonts->BlitText(61, 16, font_score, score_text);
  
		//end anim of dead and disable
		if (ToBeDeleted == true && current_animation->Finished() == true) {
			//App->powerup->Disable();
			App->player->Disable();
		}
	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider *c1, Collider *c2) {

	if (c1->type == COLLIDER_POWER_UP && c2->type == COLLIDER_PLAYER) {
		App->powerup->HOU_activated = true;
		App->powerup->colliderPowerUp->to_delete = true;
	}
	if (((c1->type == COLLIDER_TYPE::COLLIDER_ENEMY || c1->type == COLLIDER_TYPE::COLLIDER_WALL) && c2->type == COLLIDER_PLAYER) || ((c2->type == COLLIDER_TYPE::COLLIDER_ENEMY || c2->type == COLLIDER_TYPE::COLLIDER_WALL) && c1->type == COLLIDER_PLAYER)) {

			if (!GOD) {

				App->scene1background->coins -= 1;
				LOG("TE QUITO UN COIN PAPITO");
				Dead = true;
				ToBeDeleted = true;
				current_animation = &DestroyShip;
				Ship1Collider->to_delete = true;
		}
	}
}
