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
#include "ModuleUI.h"
#include "ModuleEnemies.h"
#include "ModuleSceneLvl1.h"
#include "ModuleStageClear.h"

#include <stdio.h>

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

	UI_ship.x=0; //UI_Ship
	UI_ship.y=9;
	UI_ship.w=16;
	UI_ship.h=8;
}

ModulePlayer::~ModulePlayer() {}

// Load assets
bool ModulePlayer::Start() {

	position.x = App->scene1background->position_min_limit + 20;
	position.y = SCREEN_HEIGHT / 2;

	if (IsEnabled()) {

		if (App->fonts->IsEnabled() == false)
			App->fonts->Enable();
		if (App->particles->IsEnabled() == false)
			App->particles->Enable();
		if (App->collision->IsEnabled() == false) 
			App->collision->Enable();
		if (App->powerup->IsEnabled() == false)
			App->powerup->Enable();
	}

	//Timer
	ShootTimer1 = 0;
	ShootTimer2 = 0;
    ShootTimer3 = 0;
	ShootTimer4 = 0;
	//ScoreP1 = 0;

	Appear.Reset();
	DestroyShip.Reset();

	LOG("Loading player 1 textures");
	//textures
	graphicsp1 = App->textures->Load("Images/Player/Ship&Ball_Sprite.png");

	//audio
	Shot_Sound = App->sound->LoadChunk("Audio/Shot_Sound.wav");
	MissilePower_Sound = App->sound->LoadChunk("Audio/General/016_Rocket _Launcher.wav");
	LasserBeam_Sound = App->sound->LoadChunk("Audio/General/015_Lasser_3.wav");

	//Colliders
	Ship1Collider = App->collision->AddCollider({ position.x, position.y,32,12 }, COLLIDER_PLAYER, this);


	//bools
	ToBeDeleted = false;
	Dead = false;

	//Player1Activated = false;
	current_animation = &Appear;

	WeaponType = 0;

	return true;
}

bool ModulePlayer::CleanUp() {

	LOG("Cleaning Up Player 1 Module");
	if (Ship1Collider != nullptr)
		Ship1Collider->to_delete = true;

	if (current_animation != nullptr) 
		current_animation = nullptr;

	App->powerup->HOU_activated = false;

	App->textures->Unload(graphicsp1);
	
	App->sound->UnloadChunks(Shot_Sound);
	App->sound->UnloadChunks(MissilePower_Sound);
	App->sound->UnloadChunks(LasserBeam_Sound);

	if (GOD)
		GOD = !GOD;

	return true;
}

// Update: draw background
update_status ModulePlayer::Update() {
	
	position.x += 1;

	int speed = 4;

	if (current_animation == &Appear) {
		Ship1Collider->changeCollider(COLLIDER_TYPE::COLLIDER_NONE);
		position.x=App->scene1background->position_min_limit+2;
		
		if (Appear.Finished() && current_animation!=&Standard) {
			position.x = App->scene1background->position_min_limit + 32;
			current_animation = &Standard;
			Ship1Collider->changeCollider(COLLIDER_TYPE::COLLIDER_PLAYER);
		}
	}
		if (current_animation != &DestroyShip && Appear.Finished()&& (current_animation != &Up ))
			current_animation = &Standard;
		

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
		
			if (App->input->keyboard[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN) {
				 App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, (App->player->position.x) + 200, App->player->position.y, false);
				 App->fonts->Spawned = true;
			}
			if (App->input->keyboard[SDL_SCANCODE_F7] == KEY_STATE::KEY_DOWN) {
				App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, (App->player->position.x) + 200, App->player->position.y, false);
				App->fonts->Spawned = true;
			}
			if (App->input->keyboard[SDL_SCANCODE_F8] == KEY_STATE::KEY_DOWN) {
				//App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_ZICZAC, (App->player->position.x) + 200, App->player->position.y, false);
				App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_BEE, (App->player->position.x) + 200, App->player->position.y, false);
				App->fonts->Spawned = true;
			}
			if (App->input->keyboard[SDL_SCANCODE_F9] == KEY_STATE::KEY_DOWN) {
				App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, (App->player->position.x) + 200, App->player->position.y, false);
				App->fonts->Spawned = true;
			}

			//GOD MODE
			if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN){

				//GOD = !GOD;
				if (GOD == true)
					GOD = false;
				else
					GOD = true;
			}
				

		

			//Shoot with timer:
			if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN ) {
				if (ShootTimer1 < SDL_GetTicks() - 100) {

					App->particles->AddParticle(App->particles->Laser, setFirePos().x - 10, setFirePos().y, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->ShootExplosion, setFirePos().x, setFirePos().y);

					Mix_PlayChannel(-1, Shot_Sound, 0);

					ShootTimer1 = SDL_GetTicks();
				
				}
					if (WeaponType == Shoots::MISSILES && ShootTimer2 < SDL_GetTicks() - 450) {

						App->particles->AddParticle(App->particles->MissilePower, position.x - 5, position.y + 10, COLLIDER_PLAYER_SHOT, 200);
						App->particles->AddParticle(App->particles->MissilePower, position.x - 5, position.y - 10, COLLIDER_PLAYER_SHOT, 200);

						Mix_PlayChannel(-1, MissilePower_Sound, 0);
						ShootTimer2 = SDL_GetTicks();
						
					}
					
					if (WeaponType == Shoots::LASERSHOOT && ShootTimer3 < SDL_GetTicks() - 500) {

						App->particles->AddParticle(App->particles->LaserBeam, setFirePos().x -16, setFirePos().y + 3, COLLIDER_PLAYER_LASERBEAM_SHOT);

						App->particles->AddParticle(App->particles->LaserBeamExplosion, setFirePos().x, setFirePos().y, COLLIDER_NONE);

						App->particles->AddParticle(App->particles->LaserBeamArea1, setFirePos().x + 5, setFirePos().y - 10, COLLIDER_NONE);

						for (int i = SDL_GetTicks(); i > SDL_GetTicks() + 50; i++) {
							
						}
						App->particles->AddParticle(App->particles->LaserBeamArea3, setFirePos().x, setFirePos().y - 11, COLLIDER_PLAYER_LASERBEAM_AREA_SHOT, 100 - 30);
						
						
						Mix_PlayChannel(-1, LasserBeam_Sound, 0);
						
						ShootTimer3 = SDL_GetTicks();
					}											
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

		//end anim of dead and disable
		if (ToBeDeleted == true && current_animation->Finished() == true) {
			Disable();
		}

	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider *c1, Collider *c2) {

	if (((c1->type == COLLIDER_TYPE::COLLIDER_ENEMY || c1->type == COLLIDER_TYPE::COLLIDER_WALL) && c2->type == COLLIDER_PLAYER) || ((c2->type == COLLIDER_TYPE::COLLIDER_ENEMY || c2->type == COLLIDER_TYPE::COLLIDER_WALL) && c1->type == COLLIDER_PLAYER)&&!ToBeDeleted) {

			if (!GOD) {

				LOG("P1LIFE MINUS ONE");
				Dead = true;
				ToBeDeleted = true;
				current_animation = &DestroyShip;
				//Ship1Collider->to_delete = true;
				--(App->fonts->P1Life);

		}
	}
}
