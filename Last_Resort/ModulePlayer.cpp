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

	ScoreP1 = 0;

	Appear.Reset();
	DestroyShip.Reset();

	LOG("Loading player 1 textures");
	//textures
	graphicsp1 = App->textures->Load("Images/Player/Ship&Ball_Sprite.png");
	UI_Main_Menu = App->textures->Load("Images/Stage_Clear/All_Stage_Clears.png");

	//fonts
	font = App->fonts->Load("Images/Fonts/Font_score.png", "0123456789ABCDEFGHIJKLMNPQRSTUVWXYZ_.,[]&$", 2);
	disappeartext = App->fonts->Load("Images/Fonts/Font_score.png", "0123456789ABCDEFGHIJKLMNPQRSTUVWXYZ_.,[]&$", 2);

	//audio
	Shot_Sound = App->sound->LoadChunk("Audio/Shot_Sound.wav");


	//Colliders
	Ship1Collider = App->collision->AddCollider({ position.x, position.y,32,12 }, COLLIDER_PLAYER, this);


	//bools
	ToBeDeleted = false;
	Dead = false;

	//Player1Activated = false;
	current_animation = &Appear;

	return true;
}

bool ModulePlayer::CleanUp() {

	LOG("Cleaning Up Player 1 Module");
	if (Ship1Collider != nullptr) {
		Ship1Collider = nullptr;
	}

	if (current_animation != nullptr) {
		current_animation = nullptr;
	}

	App->textures->Unload(UI_Main_Menu);
	App->textures->Unload(graphicsp1);
	App->fonts->UnLoad(font);
	App->fonts->UnLoad(disappeartext);
	
	App->sound->UnloadChunks(Shot_Sound);

	if (GOD) {
		GOD = false;
	}

	
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

			if (App->input->keyboard[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN) {
				 App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, (App->player->position.x) + 200, App->player->position.y);
				 Spawned = true;
			}
			if (App->input->keyboard[SDL_SCANCODE_F7] == KEY_STATE::KEY_DOWN) {
				App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, (App->player->position.x) + 200, App->player->position.y);
				Spawned = true;
			}
			if (App->input->keyboard[SDL_SCANCODE_F8] == KEY_STATE::KEY_DOWN) {
				App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_ZICZAC, (App->player->position.x) + 200, App->player->position.y);
				Spawned = true;
			}
			if (App->input->keyboard[SDL_SCANCODE_F9] == KEY_STATE::KEY_DOWN) {
				App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_SUICIDE, (App->player->position.x) + 200, App->player->position.y);
				Spawned = true;
			}
			
			if (App->input->keyboard[SDL_SCANCODE_F10] == KEY_STATE::KEY_DOWN) {
				if (GOD) {
					GOD = !GOD;
				}
				else if (!GOD) {
					GOD;
				}


			}

			if (GOD) {

				App->fonts->BlitText(13, SCREEN_HEIGHT - 10, font, "G0D");
				App->fonts->BlitText(39, SCREEN_HEIGHT - 10, font, "M0DE");
			}
			if (Spawned){
				//PUT FONT
				if(TimeCounter){
					AppearTime = SDL_GetTicks() + 2000;
					TimeCounter = false;
				}
				
				App->fonts->BlitText((SCREEN_WIDTH - 98), (SCREEN_HEIGHT - 10), disappeartext, "ENEMY");
				App->fonts->BlitText((SCREEN_WIDTH - 56), (SCREEN_HEIGHT - 10), disappeartext, "SPAWNED");
				if (SDL_GetTicks() >= AppearTime) {
					TimeCounter = true;
					Spawned = false;
				}
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
	

		//P1 Score
		sprintf_s(score_text, "%7d", ScoreP1);
		App->fonts->BlitText(40, 16, font, score_text);
		App->fonts->BlitText(13, 16, font, "P1");
		App->fonts->BlitText(29, 11, font, "_");
		App->fonts->BlitText(29, 15, font, "_");

		App->render->Blit(UI_Main_Menu,13 ,24,&UI_ship,0.0f,false); //Mini_UI_Ships->Player1
		

		//P1 Life
		sprintf_s(life_text, "%7d", App->scene1background->P1Coins);
		App->fonts->BlitText(30, 24, font, "X0");
		App->fonts->BlitText(-2, 24, font, life_text);

		if (App->player2->Dead == false && App->player2->IsEnabled() == false) {
			App->fonts->BlitText((SCREEN_WIDTH - 76), 16, font, "INSERT");
			App->fonts->BlitText((SCREEN_WIDTH - 74), 24, font, "COIN");
		}

		//TOP Score
		if (App->player2->IsEnabled() == true)
			TopScore = App->fonts->TopScore(ScoreP1, App->player2->ScoreP2, TopScore);
		else
			TopScore = App->fonts->TopScoreP1(ScoreP1, TopScore);

		sprintf_s(top_score, "%7d", TopScore);
		
		App->fonts->BlitText((SCREEN_WIDTH / 2) - 41, 16, font, "T0P");
		App->fonts->BlitText((SCREEN_WIDTH / 2) -9, 16, font, top_score);


		//end anim of dead and disable
		if (ToBeDeleted == true && current_animation->Finished() == true) {
			App->player->Disable();
			App->textures->Unload(graphicsp1);
			Disable();
		}
	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider *c1, Collider *c2) {

	if (((c1->type == COLLIDER_TYPE::COLLIDER_ENEMY || c1->type == COLLIDER_TYPE::COLLIDER_WALL) && c2->type == COLLIDER_PLAYER) || ((c2->type == COLLIDER_TYPE::COLLIDER_ENEMY || c2->type == COLLIDER_TYPE::COLLIDER_WALL) && c1->type == COLLIDER_PLAYER)) {

			if (!GOD) {

				--(App->scene1background->P1Coins);
				LOG("TE QUITO UN COIN PAPITO");
				Dead = true;
				ToBeDeleted = true;
				current_animation = &DestroyShip;
				Ship1Collider->to_delete = true;
		}
	}
}
