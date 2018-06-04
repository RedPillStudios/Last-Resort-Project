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


ModulePlayer2::ModulePlayer2()
{
	positionp2.x = 20;
	positionp2.y = SCREEN_HEIGHT / 4;

	Standard.PushBack({ 32,0,32,11 });

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
	Appear2.PushBack({ 390,102,32,15 });
	/*Appear.PushBack({ 128,139,64,19 });
	Appear.PushBack({ 128,158,64,19 });*/
	Appear2.speed = 0.2f;
	Appear2.loop = false;

	DestroyShip.PushBack({ 352,0,32,11 });
	DestroyShip.PushBack({ 384,0,32,12 });
	DestroyShip.PushBack({ 416,0,40,15 });
	DestroyShip.PushBack({ 459,0,32,18 });
	DestroyShip.PushBack({ 0,18,45,19 });
	DestroyShip.PushBack({ 45,18,51,20 });
	DestroyShip.PushBack({ 96,18,59,21 });
	DestroyShip.PushBack({ 155,18,63,23 });
	DestroyShip.PushBack({ 221,18,60,24 });
	DestroyShip.PushBack({ 283,18,64,23 });
	DestroyShip.PushBack({ 350,18,57,23 });
	DestroyShip.PushBack({ 410,17,55,24 });

	DestroyShip.PushBack({ 0,42,58,25 });
	DestroyShip.PushBack({ 58,42,54,26 });
	DestroyShip.PushBack({ 112,42,59,27 });
	DestroyShip.PushBack({ 174,42,57,28 });
	DestroyShip.PushBack({ 230,42,57,28 });
	DestroyShip.PushBack({ 288,42,58,27 });
	DestroyShip.PushBack({ 352,42,42,21 });
	DestroyShip.PushBack({ 399,42,38,16 });

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

	positionp2.x = App->scene1background->position_min_limit + 20;
	positionp2.y = SCREEN_WIDTH / 2;

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
																		   //collider
	Ship2Collider = App->collision->AddCollider({ 64,0,32,12 }, COLLIDER_PLAYER2, this);
	//sound
	Shot_Sound = App->sound->LoadChunk("Audio/Shot_Sound.wav");
	MissilePower_Sound = App->sound->LoadChunk("Audio/General/016_Rocket _Launcher.wav");
	LasserBeam_Sound = App->sound->LoadChunk("Audio/General/015_Lasser_3.wav");

	//bools
	Dead = false;
	AppearAnim = true;
	ToBeDeleted = false;

	//Timer
	ShootTimer1 = 0;
	ShootTimer2 = 0;
	ShootTimer3 = 0;
	ShootTimer4 = 0;
	//_____
	DestroyShip.Reset();
	current_animation2 = &Appear2;

	return true;
}

bool ModulePlayer2::CleanUp() {

	LOG("Cleaning Up Player 2 Module")
		App->textures->Unload(graphicsp2);

	if (current_animation2 != nullptr)
		current_animation2 = nullptr;


	if (Ship2Collider != nullptr)
		Ship2Collider->to_delete = true;

	App->sound->UnloadChunks(Shot_Sound);
	App->sound->UnloadChunks(MissilePower_Sound);
	App->sound->UnloadChunks(LasserBeam_Sound);

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

			if (ShootTimer1 < SDL_GetTicks() - 150) {

				App->particles->AddParticle(App->particles->Laser, setFirePos2().x - 10, setFirePos2().y, COLLIDER_PLAYER_SHOT2);
				App->particles->AddParticle(App->particles->ShootExplosion, setFirePos2().x, setFirePos2().y);

				Mix_PlayChannel(-1, Shot_Sound, 0);
				ShootTimer1 = SDL_GetTicks();
			}
			if (WeaponTypeP2 == ShootsP2::MISSILESP2 && ShootTimer2 < SDL_GetTicks() - 600) {

				App->particles->AddParticle(App->particles->MissilePower, positionp2.x - 5, positionp2.y + 10, COLLIDER_PLAYER_SHOT2, 200);
				App->particles->AddParticle(App->particles->MissilePower, positionp2.x - 5, positionp2.y - 10, COLLIDER_PLAYER_SHOT2, 200);

				Mix_PlayChannel(-1, MissilePower_Sound, 0);
				ShootTimer2 = SDL_GetTicks();
			}
			if (WeaponTypeP2 == 4 && ShootTimer2 < SDL_GetTicks() - 600) {

				App->particles->AddParticle(App->particles->MissilePower, positionp2.x - 5, positionp2.y + 10, COLLIDER_PLAYER_SHOT2, 200);
				App->particles->AddParticle(App->particles->MissilePower, positionp2.x - 5, positionp2.y - 10, COLLIDER_PLAYER_SHOT2, 200);

				App->particles->AddParticle(App->particles->MissilePower, positionp2.x - 10, positionp2.y + 20, COLLIDER_PLAYER_SHOT2, 200);
				App->particles->AddParticle(App->particles->MissilePower, positionp2.x - 10, positionp2.y - 20, COLLIDER_PLAYER_SHOT2, 200);

				App->particles->AddParticle(App->particles->MissilePower, positionp2.x - 15, positionp2.y + 30, COLLIDER_PLAYER_SHOT2, 200);
				App->particles->AddParticle(App->particles->MissilePower, positionp2.x - 15, positionp2.y - 30, COLLIDER_PLAYER_SHOT2, 200);

				Mix_PlayChannel(-1, MissilePower_Sound, 0);
				ShootTimer2 = SDL_GetTicks();

			}

			if (WeaponTypeP2 == ShootsP2::LASERSHOOTP2 && ShootTimer3 < SDL_GetTicks() - 650) {

				App->particles->AddParticle(App->particles->LaserBeam, setFirePos2().x - 16, setFirePos2().y + 3, COLLIDER_PLAYER_LASERBEAM_SHOT2);
				App->particles->AddParticle(App->particles->LaserBeamExplosion, setFirePos2().x, setFirePos2().y, COLLIDER_NONE);
				App->particles->AddParticle(App->particles->LaserBeamArea1, setFirePos2().x + 5, setFirePos2().y - 10, COLLIDER_NONE);
			//	App->particles->AddParticle(App->particles->LaserBeamArea3, setFirePos2().x, setFirePos2().y - 11, COLLIDER_PLAYER_LASERBEAM_AREA_SHOT2, 100 - 30);

				Mix_PlayChannel(-1, LasserBeam_Sound, 0);
				ShootTimer3 = SDL_GetTicks();
			}
			if (WeaponTypeP2 == 5 && ShootTimer3 < SDL_GetTicks() - 650) {

				App->particles->AddParticle(App->particles->LaserBeam, setFirePos2().x - 16, setFirePos2().y + 3, COLLIDER_PLAYER_LASERBEAM_SHOT2);
				App->particles->AddParticle(App->particles->LaserBeamExplosion, setFirePos2().x, setFirePos2().y, COLLIDER_NONE);
				App->particles->AddParticle(App->particles->LaserBeamArea1, setFirePos2().x + 5, setFirePos2().y - 10, COLLIDER_NONE);
				App->particles->AddParticle(App->particles->LaserBeamArea3, setFirePos2().x, setFirePos2().y - 11, COLLIDER_PLAYER_LASERBEAM_AREA_SHOT2, 100 - 30);

				Mix_PlayChannel(-1, LasserBeam_Sound, 0);
				ShootTimer3 = SDL_GetTicks();
			}
		}
	}

	Ship2Collider->SetPos(positionp2.x, positionp2.y);
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

	//end anim of dead and disable
	if (ToBeDeleted == true && current_animation2->Finished() == true) {
		Disable();
	}

	return UPDATE_CONTINUE;
}

void ModulePlayer2::OnCollision(Collider *c1, Collider *c2) {

	if (((c1->type == COLLIDER_TYPE::COLLIDER_ENEMY || c1->type == COLLIDER_TYPE::COLLIDER_WALL) && c2->type == COLLIDER_PLAYER2) || ((c2->type == COLLIDER_TYPE::COLLIDER_ENEMY || c2->type == COLLIDER_TYPE::COLLIDER_WALL) && c1->type == COLLIDER_PLAYER2) && !ToBeDeleted) {

		if (!GOD) {

			LOG("TE QUITO UN COIN MAMASITA");
			Dead = true;
			current_animation2 = &DestroyShip;
			ToBeDeleted = true;
			//Ship2Collider->to_delete = true;
			--(App->fonts->P2Life);
		}
	}
}

void ModulePlayer2::ShootSelector(uint shoot) {

	if (shoot == BASICSHOOTP2) 
		WeaponTypeP2 = 0;
	else if (shoot == LASERSHOOTP2) 
		WeaponTypeP2 = 2;
	else if (shoot == MISSILESP2) 
		WeaponTypeP2 = 3;
	
}