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
#include "ModuleSceneLvl1.h"
#include "ModuleUI.h"
#include "ModuleStageClear.h"
#include "ModuleMainMenu.h"

#include <stdio.h>
// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA


ModulePlayer2::ModulePlayer2()
{
	positionp2.x = 20;
	positionp2.y = SCREEN_HEIGHT / 4;

	Standard.PushBack({32,0,32,11});

	Up.PushBack({ 128,0,32,11 });
	Up.PushBack({ 160,0,32,11 });
	Up.speed = 0.10f;
	Up.loop = false;

	Down.PushBack({ 64,0,32,12 });
	Down.PushBack({ 94,0,32,11 });
	Down.speed = 0.10f;
	Down.loop = false;

	Appear2.PushBack({ 0,102,62,15 });
	Appear2.PushBack({ 62,102,51,16 });
	Appear2.PushBack({ 113,102,64,16 });
	Appear2.PushBack({ 177,102,64,25 });
	Appear2.PushBack({ 241,102,57,25 });
	Appear2.PushBack({ 298,102,56,25 });
	Appear2.PushBack({ 353,102,36,19 });
	Appear2.PushBack({390,102,32,15 });
	/*Appear.PushBack({ 128,139,64,19 });
	Appear.PushBack({ 128,158,64,19 });*/
	Appear2.speed = 0.2f;
	Appear2.loop = false;

	DestroyShip.PushBack({ 352,0,32,11 });
	DestroyShip.PushBack({ 384,0,32,12 });
	DestroyShip.PushBack({416,0,40,15});
	DestroyShip.PushBack({459,0,32,18 });
	DestroyShip.PushBack({ 0,18,45,19});
	DestroyShip.PushBack({45,18,51,20 });
	DestroyShip.PushBack({96,18,59,21});
	DestroyShip.PushBack({155,18,63,23  });
	DestroyShip.PushBack({221,18,60,24 });
	DestroyShip.PushBack({283,18,64,23  });
	DestroyShip.PushBack({350,18,57,23 });
	DestroyShip.PushBack({410,17,55,24 });

	DestroyShip.PushBack({0,42,58,25});
	DestroyShip.PushBack({58,42,54,26});
	DestroyShip.PushBack({112,42,59,27});
	DestroyShip.PushBack({174,42,57,28});
	DestroyShip.PushBack({230,42,57,28 });
	DestroyShip.PushBack({288,42,58,27});
	DestroyShip.PushBack({352,42,42,21 });
	DestroyShip.PushBack({399,42,38,16 });

	DestroyShip.speed = 0.3f;
	DestroyShip.loop = false;

	UI_ship2.x = 168;
	UI_ship2.y = 25;
	UI_ship2.w = 17;
	UI_ship2.h = 6;
}

ModulePlayer2::~ModulePlayer2() {}

// Load assets
bool ModulePlayer2::Start() {

	ScoreP2 = App->fonts->SP2;
	positionp2.x = App->scene1background->position_min_limit + 20;
	positionp2.y = SCREEN_WIDTH/2;

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

	LOG("Loading player2 textures");
	Appear2.Reset();
	//textures
	graphicsp2 = App->textures->Load("Images/Player/Player2_Spirtes.png"); // arcade version
	UI_Main_Menu= App->textures->Load("Images/Stage_Clear/All_Stage_Clears.png");
	//fonts
	font2 = App->fonts->Load("Images/Fonts/Font_score.png", "0123456789ABCDEFGHIJKLMNPQRSTUVWXYZ_.,[]&$", 2);
	//collider
	Ship2Collider = App->collision->AddCollider({ 64,0,32,12 }, COLLIDER_PLAYER, this);
	//sound
	Shot_Sound = App->sound->LoadChunk("Audio/Shot_Sound.wav");

	//initializing
	ScoreP2 = 0;
	TopScore;


	//bools
	Dead = false;
	AppearAnim = true;
	ToBeDeleted = false;
	

	DestroyShip.Reset();
	current_animation2 = &Appear2;

	return true;
}

bool ModulePlayer2::CleanUp() {

	LOG("Cleaning Up Player 2 Module")
	App->textures->Unload(graphicsp2);
	App->textures->Unload(UI_Main_Menu);

	if (current_animation2 != nullptr) 
		current_animation2 = nullptr;
	
	
	if (Ship2Collider != nullptr) 
		Ship2Collider->to_delete = true;
	
	App->fonts->UnLoad(font2);

	App->sound->UnloadChunks(Shot_Sound);
	
	return true;
}

// Update: draw background
update_status ModulePlayer2::Update() {

	positionp2.x += 1;

	int speed = 2;

	if (current_animation2 == &Appear2) {
		positionp2.x = App->scene1background->position_min_limit + 2;
		if (Appear2.Finished()) {
			positionp2.x = App->scene1background->position_min_limit + 32;
			current_animation2 = &Standard;
		}
	}

	if (current_animation2 != &DestroyShip && Appear2.Finished()) {
		current_animation2 = &Standard;
	}


	if (!Dead&& current_animation2 != &Appear2) {
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
			while (positionp2.x >= App->scene1background->position_max_limit - 32) {
				positionp2.x = App->scene1background->position_max_limit - 32;
				break;
			}
		}
		/*Movement left*/
		if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT) {
			positionp2.x -= speed;
			while (positionp2.x <= App->scene1background->position_min_limit + 2) {
				positionp2.x = App->scene1background->position_min_limit + 2;
				break;
			}
		}
		if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN)
				GOD = !GOD;
			
		/*Shoot*/
		if (App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_DOWN) {

			App->particles->AddParticle(App->particles->Laser, setFirePos2().x, setFirePos2().y, COLLIDER_PLAYER_SHOT2);
			App->particles->AddParticle(App->particles->ShootExplosion, setFirePos2().x, setFirePos2().y);
			Mix_PlayChannel(-1, Shot_Sound, 0);
		}
	}

	/* Draw everything --------------------------------------*/

	if (current_animation2 == &Appear2) {
		App->render->Blit(graphicsp2, positionp2.x, positionp2.y, &(current_animation2->GetCurrentFrame()));
	}
	else if (current_animation2 == &DestroyShip) {
		App->render->Blit(graphicsp2, positionp2.x, positionp2.y, &(current_animation2->GetCurrentFrame()));
	}
	else {
		App->render->Blit(graphicsp2, positionp2.x, positionp2.y, &(current_animation2->GetCurrentFrame()));
	}

	Ship2Collider->SetPos(positionp2.x, positionp2.y);

	//P2 Score
	sprintf_s(score_text2, "%7d", ScoreP2);
	App->fonts->BlitText((SCREEN_WIDTH - 65), 16, App->player->font, score_text2);
	App->fonts->BlitText((SCREEN_WIDTH - 76), 11, App->player->font, "_");
	App->fonts->BlitText((SCREEN_WIDTH - 76), 15, App->player->font, "_");
	App->fonts->BlitText((SCREEN_WIDTH - 92), 16, App->player->font, "P2");

	App->render->Blit(UI_Main_Menu,237,24,&UI_ship2,0.0f,false); //Mini_UI_Ships->Player2

	//P2 Life
	sprintf_s(life_text, "%7d", App->scene1background->P2Coins);
	App->fonts->BlitText((SCREEN_WIDTH - 75), 24, App->player->font, "X0");
	App->fonts->BlitText((SCREEN_WIDTH - 107), 24, App->player->font, life_text);

	if (App->player->Dead == true && App->player->IsEnabled() == false) {
		
		if (App->player->IsEnabled() == true)
			TopScore = App->fonts->TopScore(App->player->ScoreP1, ScoreP2, TopScore);
		else
			TopScore = App->fonts->TopScoreP1(App->player->ScoreP1, TopScore);

		sprintf_s(top_score, "%7d", TopScore);
		App->fonts->BlitText((SCREEN_WIDTH / 2) - 41, 16, font2, "T0P");
		App->fonts->BlitText((SCREEN_WIDTH / 2) - 9, 16, font2, top_score);
	}


	//end anim of dead and disable
	if (ToBeDeleted == true && current_animation2->Finished() == true) {
		Disable();
		App->textures->Unload(graphicsp2);
	}

	return UPDATE_CONTINUE;
}

void ModulePlayer2::OnCollision(Collider *c1, Collider *c2) {

	if (((c1->type == COLLIDER_TYPE::COLLIDER_ENEMY || c1->type == COLLIDER_TYPE::COLLIDER_WALL) && c2->type == COLLIDER_PLAYER) || ((c2->type == COLLIDER_TYPE::COLLIDER_ENEMY || c2->type == COLLIDER_TYPE::COLLIDER_WALL) && c1->type == COLLIDER_PLAYER)) {
		
		if (!GOD) {
			App->fonts->SP2 = ScoreP2;
			App->scene1background->P2Coins -= 1;
			LOG("TE QUITO UN COIN MAMASITA");
			Dead = true;
			current_animation2 = &DestroyShip;
			ToBeDeleted = true;
			Ship2Collider->to_delete = true;
		}
	}
}