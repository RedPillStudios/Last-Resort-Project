#include "Application.h"
#include "ModulePowerUp.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleInput.h"
#include "Module_Hou_Player1.h"
#include <math.h>

#define SPAWN_MARGIN 50


ModuleHouPlayer1::ModuleHouPlayer1() {

	int counter = 0;

	//BLUE BALL
	for (uint i = 0; i <= 7; ++i) {
		Blue_HOU_Front_Up_Up.PushBack({ 261,counter,17,23 });
		counter += 23;
		if (counter >= 184)
			counter = 0;
	}
	Blue_HOU_Front_Up_Up.speed = 0.4f;

	for (uint i = 0; i <= 7; ++i) {
		Blue_HOU_Front_Up_Down.PushBack({ 218,counter,22,17 });
		counter += 17;
		if (counter >= 136)
			counter = 0;
	}
	Blue_HOU_Front_Up_Down.speed = 0.4f;

	for (uint i = 0; i <= 7; ++i) {
		Blue_HOU_Front_Down_Up.PushBack({ 490,counter,22,17 });
		counter += 17;
		if (counter >= 136)
			counter = 0;
	}
	Blue_HOU_Front_Down_Up.speed = 0.4f;

	for (uint i = 0; i <= 7; ++i) {
		Blue_HOU_Front_Down_Down.PushBack({ 452,counter,17,23 });
		counter += 23;
		if (counter >= 184)
			counter = 0;
	}
	Blue_HOU_Front_Down_Down.speed = 0.4f;



	for (uint i = 0; i <= 7; ++i) {
		Blue_HOU_Front_Up.PushBack({ 240,counter,21,21 });
		counter += 21;
		if (counter >= 168)
			counter = 0;
	}

	Blue_HOU_Front_Up.speed = 0.4f;

	for (uint i = 0; i <= 7; i++) {
		Blue_HOU_Front_Down.PushBack({ 469,counter,21,21 });
		counter += 21;
		if (counter >= 168)
			counter = 0;
	}
	Blue_HOU_Front_Down.speed = 0.4f;

	for (uint i = 0; i <= 7; ++i) {
		Blue_HOU_Back_Up_Up.PushBack({ 294,counter,17,23 });
		counter += 23;
		if (counter >= 184)
			counter = 0;
	}
	Blue_HOU_Back_Up_Up.speed = 0.4f;

	for (uint i = 0; i <= 7; ++i) {
		Blue_HOU_Back_Up_Down.PushBack({ 332,counter,22,17 });
		counter += 17;
		if (counter >= 136)
			counter = 0;
	}
	Blue_HOU_Back_Up_Down.speed = 0.4f;

	for (uint i = 0; i <= 7; ++i) {
		Blue_HOU_Back_Down_Up.PushBack({ 376,counter,22,17 });
		counter += 17;
		if (counter >= 136)
			counter = 0;
	}
	Blue_HOU_Back_Down_Up.speed = 0.4f;

	for (uint i = 0; i <= 7; ++i) {
		Blue_HOU_Back_Down_Down.PushBack({ 419,counter,17,23 });
		counter += 23;
		if (counter >= 184)
			counter = 0;
	}
	Blue_HOU_Back_Down_Down.speed = 0.4f;

	for (uint i = 0; i <= 7; i++) {
		Blue_HOU_Back_Down.PushBack({ 398,counter,21,21 });
		counter += 21;
		if (counter >= 168)
			counter = 0;
	}
	Blue_HOU_Back_Down.speed = 0.4f;


	for (uint i = 0; i <= 7; i++) {
		Blue_HOU_Back_UP.PushBack({ 311,counter,21,21 });
		counter += 21;
		if (counter >= 168)
			counter = 0;
	}
	Blue_HOU_Back_UP.speed = 0.4f;
	Blue_Throw_Ball.PushBack({ 140,178,26,26 });
	Blue_Throw_Ball.PushBack({ 140,204,26,26 });
	Blue_Throw_Ball.PushBack({ 141,230,26,26 });
	Blue_Throw_Ball.PushBack({ 141,256,26,26 });
	Blue_Throw_Ball.PushBack({ 140,282,26,26 });
	Blue_Throw_Ball.PushBack({ 139,308,26,26 });
	Blue_Throw_Ball.speed = 0.2f;

	Blue_HOU_Front.PushBack({ 195,0,22,16 });
	Blue_HOU_Front.PushBack({ 195,16,22,16 });
	Blue_HOU_Front.PushBack({ 195,32,22,16 });
	Blue_HOU_Front.PushBack({ 195,48,22,16 });
	Blue_HOU_Front.PushBack({ 195,64,22,16 });
	Blue_HOU_Front.PushBack({ 195,80,22,16 });
	Blue_HOU_Front.PushBack({ 195,96,22,16 });
	Blue_HOU_Front.PushBack({ 195,112,22,16 });
	Blue_HOU_Front.loop = true;
	Blue_HOU_Front.speed = 0.4f;

	Blue_HOU_Back.PushBack({ 354,0,22,16 });
	Blue_HOU_Back.PushBack({ 354,16,22,16 });
	Blue_HOU_Back.PushBack({ 354,32,22,16 });
	Blue_HOU_Back.PushBack({ 354,48,22,16 });
	Blue_HOU_Back.PushBack({ 354,64,22,16 });
	Blue_HOU_Back.PushBack({ 354,80,22,16 });
	Blue_HOU_Back.PushBack({ 354,96,22,16 });
	Blue_HOU_Back.PushBack({ 354,112,22,16 });
	Blue_HOU_Back.loop = true;
	Blue_HOU_Back.speed = 0.4f;

	Blue_HOU_UP.PushBack({ 278,0,16,22 });
	Blue_HOU_UP.PushBack({ 278,22,16,22 });
	Blue_HOU_UP.PushBack({ 278,44,16,22 });
	Blue_HOU_UP.PushBack({ 278,66,16,22 });
	Blue_HOU_UP.PushBack({ 278,88,16,22 });
	Blue_HOU_UP.PushBack({ 278,110,16,22 });
	Blue_HOU_UP.PushBack({ 278,132,16,22 });
	Blue_HOU_UP.PushBack({ 278,154,16,22 });
	Blue_HOU_UP.loop = true;
	Blue_HOU_UP.speed = 0.4f;

	Blue_HOU_Down.PushBack({ 436,0,16,22 });
	Blue_HOU_Down.PushBack({ 436,22,16,22 });
	Blue_HOU_Down.PushBack({ 436,44,16,22 });
	Blue_HOU_Down.PushBack({ 436,66,16,22 });
	Blue_HOU_Down.PushBack({ 436,88,16,22 });
	Blue_HOU_Down.PushBack({ 436,110,16,22 });
	Blue_HOU_Down.PushBack({ 436,132,16,22 });
	Blue_HOU_Down.PushBack({ 436,154,16,22 });
	Blue_HOU_Down.loop = true;
	Blue_HOU_Down.speed = 0.4f;

	Blue_Charge.PushBack({ 0,0,47,47 });
	Blue_Charge.PushBack({ 47,0,47,47 });
	Blue_Charge.PushBack({ 94,0,47,47 });
	Blue_Charge.PushBack({ 141,0,47,47 });
	Blue_Charge.PushBack({ 188,0,47,47 });
	Blue_Charge.PushBack({ 0,47,47,47 });
	Blue_Charge.PushBack({ 47,47,47,47 });
	Blue_Charge.PushBack({ 94,47,47,47 });
	Blue_Charge.PushBack({ 141,47,47,47 });
	Blue_Charge.PushBack({ 188,47,47,47 });
	Blue_Charge.PushBack({ 0,94,47,47 });
	Blue_Charge.PushBack({ 47,94,47,47 });
	Blue_Charge.PushBack({ 94,94,47,47 });
	Blue_Charge.PushBack({ 141,94,47,47 });
	Blue_Charge.PushBack({ 188,94,47,47 });

	Blue_Charge.loop = true;
	Blue_Charge.speed = 0.4f;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 5; ++j)
			blueball_charging.PushBack({ 230 + 46 * j,45 + 46 * i,46,46 });
	}
	blueball_charging.speed = 0.3;


	//RED BALL
	int counter2 = 184;
	for (uint i = 0; i <= 7; ++i) {
		Red_HOU_Front_Up_Up.PushBack({ 261,counter2,17,23 });
		counter2 += 23;
		if (counter2 > 345)
			counter2 = 184;
	}
	Red_HOU_Front_Up_Up.speed = 0.4f;



	for (uint i = 0; i <= 7; ++i) {
		Red_HOU_Front_Up_Down.PushBack({ 218,counter2,22,17 });
		counter2 += 17;
		if (counter2 > 303)
			counter2 = 184;
	}
	Red_HOU_Front_Up_Down.speed = 0.4f;



	for (uint i = 0; i <= 7; ++i) {
		Red_HOU_Front_Down_Up.PushBack({ 490,counter2,22,17 });
		counter2 += 17;
		if (counter2 > 303)
			counter2 = 184;
	}
	Red_HOU_Front_Down_Up.speed = 0.4f;



	for (uint i = 0; i <= 7; ++i) {
		Red_HOU_Front_Down_Down.PushBack({ 452,counter2,17,23 });
		counter2 += 23;
		if (counter2 >345)
			counter2 = 184;
	}
	Red_HOU_Front_Down_Down.speed = 0.4f;



	for (uint i = 0; i <= 7; ++i) {
		Red_HOU_Front_Up.PushBack({ 240,counter2,21,21 });
		counter2 += 21;
		if (counter2 > 331)
			counter2 = 184;
	}

	Red_HOU_Front_Up.speed = 0.4f;

	for (uint i = 0; i <= 7; i++) {
		Red_HOU_Front_Down.PushBack({ 469,counter2,21,21 });
		counter2 += 21;
		if (counter2 > 331)
			counter2 = 184;
	}
	Red_HOU_Front_Down.speed = 0.4f;

	for (uint i = 0; i <= 7; ++i) {
		Red_HOU_Back_Up_Up.PushBack({ 294,counter2,17,23 });
		counter2 += 23;
		if (counter2 > 345)
			counter2 = 184;
	}
	Red_HOU_Back_Up_Up.speed = 0.4f;

	for (uint i = 0; i <= 7; ++i) {
		Red_HOU_Back_Up_Down.PushBack({ 332,counter2,22,17 });
		counter2 += 17;
		if (counter2 > 303)
			counter2 = 184;
	}
	Red_HOU_Back_Up_Down.speed = 0.4f;

	for (uint i = 0; i <= 7; ++i) {
		Red_HOU_Back_Down_Up.PushBack({ 376,counter2,22,17 });
		counter2 += 17;
		if (counter2 > 303)
			counter2 = 184;
	}
	Red_HOU_Back_Down_Up.speed = 0.4f;

	for (uint i = 0; i <= 7; ++i) {
		Red_HOU_Back_Down_Down.PushBack({ 419,counter2,17,23 });
		counter2 += 23;
		if (counter2 > 345)
			counter2 = 184;
	}
	Red_HOU_Back_Down_Down.speed = 0.4f;

	for (uint i = 0; i <= 7; i++) {
		Red_HOU_Back_Down.PushBack({ 398,counter2,21,21 });
		counter2 += 21;
		if (counter2 > 331)
			counter2 = 184;
	}
	Red_HOU_Back_Down.speed = 0.4f;


	for (uint i = 0; i <= 7; i++) {
		Red_HOU_Back_UP.PushBack({ 311,counter2,21,21 });
		counter2 += 21;
		if (counter2 > 336)
			counter2 = 184;
	}
	Red_HOU_Back_UP.speed = 0.4f;

	Red_Throw_Ball.PushBack({ 166,178,26,26 });
	Red_Throw_Ball.PushBack({ 166,204,26,26 });
	Red_Throw_Ball.PushBack({ 167,230,26,26 });
	Red_Throw_Ball.PushBack({ 167,256,26,26 });
	Red_Throw_Ball.PushBack({ 166,282,26,26 });
	Red_Throw_Ball.PushBack({ 165,308,26,26 });
	Red_Throw_Ball.speed = 0.2f;

	Red_HOU_Front.PushBack({ 195,184,22,16 });
	Red_HOU_Front.PushBack({ 195,200,22,16 });
	Red_HOU_Front.PushBack({ 195,216,22,16 });
	Red_HOU_Front.PushBack({ 195,232,22,16 });
	Red_HOU_Front.PushBack({ 195,248,22,16 });
	Red_HOU_Front.PushBack({ 195,264,22,16 });
	Red_HOU_Front.PushBack({ 195,280,22,16 });
	Red_HOU_Front.PushBack({ 195,296,22,16 });
	Red_HOU_Front.loop = true;
	Red_HOU_Front.speed = 0.4f;

	Red_HOU_Back.PushBack({ 354,184,22,16 });
	Red_HOU_Back.PushBack({ 354,200,22,16 });
	Red_HOU_Back.PushBack({ 354,216,22,16 });
	Red_HOU_Back.PushBack({ 354,232,22,16 });
	Red_HOU_Back.PushBack({ 354,248,22,16 });
	Red_HOU_Back.PushBack({ 354,264,22,16 });
	Red_HOU_Back.PushBack({ 354,280,22,16 });
	Red_HOU_Back.PushBack({ 354,296,22,16 });
	Red_HOU_Back.loop = true;
	Red_HOU_Back.speed = 0.4f;

	Red_HOU_UP.PushBack({ 278,184,16,22 });
	Red_HOU_UP.PushBack({ 278,206,16,22 });
	Red_HOU_UP.PushBack({ 278,228,16,22 });
	Red_HOU_UP.PushBack({ 278,250,16,22 });
	Red_HOU_UP.PushBack({ 278,272,16,22 });
	Red_HOU_UP.PushBack({ 278,294,16,22 });
	Red_HOU_UP.PushBack({ 278,316,16,22 });
	Red_HOU_UP.PushBack({ 278,338,16,22 });
	Red_HOU_UP.loop = true;
	Red_HOU_UP.speed = 0.4f;

	Red_HOU_Down.PushBack({ 436,184,16,22 });
	Red_HOU_Down.PushBack({ 436,206,16,22 });
	Red_HOU_Down.PushBack({ 436,228,16,22 });
	Red_HOU_Down.PushBack({ 436,250,16,22 });
	Red_HOU_Down.PushBack({ 436,272,16,22 });
	Red_HOU_Down.PushBack({ 436,294,16,22 });
	Red_HOU_Down.PushBack({ 436,316,16,22 });
	Red_HOU_Down.PushBack({ 436,338,16,22 });
	Red_HOU_Down.loop = true;
	Red_HOU_Down.speed = 0.4f;


	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 5; ++j)
			Redball_charging.PushBack({ 0 + 46 * j,45 + 46 * i,46,46 });
	}
	Redball_charging.speed = 0.3;





}

ModuleHouPlayer1::~ModuleHouPlayer1() {}

bool ModuleHouPlayer1::Start() {

	//HOU_position_x = App->player->position.x;
	//HOU_position_y = App->player->position.y;

	LOG("Loading PowerUps");
	if (App->player->IsEnabled() == true && App->HOU_Player1->IsEnabled() == false)
		App->HOU_Player1->Enable();

	ChargeHOUSound = App->sound->LoadChunk("Audio/General/Charging_shot.wav");
	ReleasedChargeHOUSound = App->sound->LoadChunk("Audio/General/Releasing_Charged_shot.wav");

	HOU_Texture = App->textures->Load("Images/Player/Ship&Ball_Sprite.png");
	Charge_texture = App->textures->Load("Images/Player/Charge_Ball.png");

	Mix_VolumeChunk(ReleasedChargeHOUSound, MIX_MAX_VOLUME / 2);

	HOU_activated = false;
	fixed = false;

	colliderHUB = App->collision->AddCollider({ -2000,-200,22,16 }, COLLIDER_HOU, this);


	return true;
}

bool ModuleHouPlayer1::CleanUp() {

	LOG("Cleaning Up Power Ups");
	App->textures->Unload(HOU_Texture);
	App->textures->Unload(Charge_texture);

	if (colliderHUB != nullptr) {
		colliderHUB = nullptr;
	}
	if (current_animation != nullptr) {
		current_animation = nullptr;
	}

	App->sound->UnloadChunks(ChargeHOUSound);
	App->sound->UnloadChunks(ReleasedChargeHOUSound);

	return true;
}


update_status ModuleHouPlayer1::Update() {


	shipCenter.x = App->player->position.x + 10;
	shipCenter.y = App->player->position.y;

	if (HOU_activated) {
		if (HOU_Direction >= 360) {
			HOU_Direction = 0;
		}
		if (HOU_Charge > 40 && App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_UP&&Throwing == false) {
			Throwing = true;
			Throw = true;
		}

		if (charging) {



		}

		if (!Throwing) {

			Hou_Movement();
			if (HOU_Direction >= 0 && HOU_Direction < 15) {
				if(Blue)
				current_animation = &Blue_HOU_Front;
				else
				current_animation = &Red_HOU_Front;
			}
			else if (HOU_Direction >= 15 && HOU_Direction < 35) {
				if (Blue)
				current_animation = &Blue_HOU_Front_Down_Up;
				else
				current_animation = &Red_HOU_Front_Down_Up;
			}
			else if (HOU_Direction >= 35 && HOU_Direction < 55) {
				if (Blue)
				current_animation = &Blue_HOU_Front_Down;
				else
				current_animation = &Red_HOU_Front_Down;
			}
			else if (HOU_Direction >= 55 && HOU_Direction < 75) {
				if (Blue)
				current_animation = &Blue_HOU_Front_Down_Down;
				else
				current_animation = &Red_HOU_Front_Down_Down;
			}
			else if (HOU_Direction >= 75 && HOU_Direction < 105) {
				if (Blue)
				current_animation = &Blue_HOU_Down;
				else
				current_animation = &Red_HOU_Down;
			}
			else if (HOU_Direction >= 105 && HOU_Direction < 125) {
				if (Blue)
				current_animation = &Blue_HOU_Back_Down_Down;
				else
				current_animation = &Red_HOU_Back_Down_Down;
			}
			else if (HOU_Direction >= 125 && HOU_Direction < 145) {
				if (Blue)
				current_animation = &Blue_HOU_Back_Down;
				else
				current_animation = &Red_HOU_Back_Down;
			}
			else if (HOU_Direction >= 145 && HOU_Direction < 165) {
				if (Blue)
				current_animation = &Blue_HOU_Back_Down_Up;
				else
				current_animation = &Red_HOU_Back_Down_Up;
			}
			else if (HOU_Direction >= 165 && HOU_Direction < 195) {
				if (Blue)
				current_animation = &Blue_HOU_Back;
				else
				current_animation = &Red_HOU_Back;
			}
			else if (HOU_Direction >= 195 && HOU_Direction < 215) {
				if (Blue)
				current_animation = &Blue_HOU_Back_Up_Down;
				else
				current_animation = &Red_HOU_Back_Up_Down;
			}
			else if (HOU_Direction >= 215 && HOU_Direction < 225) {
				if (Blue)
				current_animation = &Blue_HOU_Back_UP;
				else
				current_animation = &Red_HOU_Back_UP;
			}
			else if (HOU_Direction >= 225 && HOU_Direction < 255) {
				if (Blue)
				current_animation = &Blue_HOU_Back_Up_Up;
				else
				current_animation = &Red_HOU_Back_Up_Up;
			}
			else if (HOU_Direction >= 255 && HOU_Direction < 285) {
				if (Blue)
				current_animation = &Blue_HOU_UP;
				else
				current_animation = &Red_HOU_UP;
			}
			else if (HOU_Direction >= 285 && HOU_Direction < 305) {
				if (Blue)
				current_animation = &Blue_HOU_Front_Up_Up;
				else
				current_animation = &Red_HOU_Front_Up_Up;
			}
			else if (HOU_Direction >= 305 && HOU_Direction < 325) {
				if (Blue)
				current_animation = &Blue_HOU_Front_Up;
				else
				current_animation = &Red_HOU_Front_Up;
			}
			else if (HOU_Direction >= 325 && HOU_Direction < 345) {
				if (Blue)
				current_animation = &Blue_HOU_Front_Up_Down;
				else
				current_animation = &Red_HOU_Front_Up_Down;
			}
			else if (HOU_Direction >= 345 && HOU_Direction <= 360) {
				if (Blue)
				current_animation = &Blue_HOU_Front;
				else
				current_animation = &Red_HOU_Front;
			}


			//Settinng Grpah position HOU

			HOU_position.x = shipCenter.x + 40 * cos(HOU_Direction*PI / 180);
			HOU_position.y = shipCenter.y + 30 * sin(HOU_Direction*PI / 180);

		}
		//Render HOU
		if (Throwing) {
			Animation* Sup = current_animation;
			if (Blue) {
				current_animation = &Blue_Throw_Ball;

			}
			else {
				current_animation = &Red_Throw_Ball;
			}
			if (Throw == true) {
				throwHOU();
				if (HOU_position.x + 17 >= App->scene1background->position_max_limit || HOU_position.y + 17 >= SCREEN_HEIGHT || HOU_position.x <= App->scene1background->position_min_limit || HOU_position.y <= 0) {
					HOUreachPosition = true;
					Throw = false;
				}
			}
			HOU_LastPosition.x = shipCenter.x + 40 * cos(HOU_Direction*PI / 180);
			HOU_LastPosition.y = shipCenter.y + 30 * sin(HOU_Direction*PI / 180);

			if (HOUreachPosition) {
				HOU_position.x++;
				HOU_position.x = HOU_position.x + 0.05*(shipCenter.x - HOU_position.x);
				HOU_position.y = HOU_position.y + 0.05*(shipCenter.y - HOU_position.y);
				if ((HOU_position.x < shipCenter.x + 30 && HOU_position.x > shipCenter.x - 30) && (HOU_position.y<shipCenter.y + 30 && HOU_position.y>shipCenter.y - 30)) {
					current_animation = Sup;

					HOUreachPosition = false;
					HOU_Charge = 0;
					Throwing = false;
				}
			}
		}

		App->particles->HOU_Shot.Speed.x = (7 * cos(HOU_Direction*PI / 180));
		App->particles->HOU_Shot.Speed.y = (7 * sin(HOU_Direction*PI / 180));

		colliderHUB->SetPos(HOU_position.x, HOU_position.y);

		App->render->Blit(HOU_Texture, HOU_position.x, HOU_position.y, &current_animation->GetCurrentFrame());
	}

	return UPDATE_CONTINUE;
}

void ModuleHouPlayer1::OnCollision(Collider *c1, Collider *c2) {

}


void ModuleHouPlayer1::throwHOU() {
	Mix_FadeOutChannel(2, 400);//fading out channel
	Mix_PlayChannel(-1, ReleasedChargeHOUSound, 0);//releasing sound
	particlesTimmer++;
	HOU_position.x++;
	HOU_position.x += (10 * cos(HOU_Direction*PI / 180));
	HOU_position.y += (10 * sin(HOU_Direction*PI / 180));
	App->particles->Red_ThrowBall_pl1.Speed.x = (1 * cos(HOU_Direction*PI / 180));
	App->particles->Red_ThrowBall_pl1.Speed.x++;
	App->particles->Red_ThrowBall_pl1.Speed.y = (1 * sin(HOU_Direction*PI / 180));


	if (particlesTimmer >= 3) {
		App->particles->AddParticle(App->particles->Red_ThrowBall_pl1, HOU_position.x, HOU_position.y, COLLIDER_NONE);
		particlesTimmer = 0;
	}

}

void ModuleHouPlayer1::returnHOU() {
	HOU_position.x = shipCenter.x - (10 * cos(HOU_Direction*PI / 180));
	HOU_position.y = shipCenter.y - (10 * sin(HOU_Direction*PI / 180));
}
void ModuleHouPlayer1::Hou_Movement() {

	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) {

		if (HOU_Direction <= 270 && HOU_Direction > 90) {
			HOU_Direction -= HOU_Speed;
		}
		else if (HOU_Direction > 270) {
			HOU_Direction += HOU_Speed;
		}
		if (HOU_Direction >= 0 && HOU_Direction < 90) {
			HOU_Direction += HOU_Speed;
		}

	}

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) {
		if (HOU_Direction <= 180 && HOU_Direction > 0) {
			HOU_Direction -= HOU_Speed;
		}
		if (HOU_Direction > 180 && HOU_Direction != 0) {
			HOU_Direction += HOU_Speed;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) {

		if (HOU_Direction < 270 && HOU_Direction >= 90) {
			HOU_Direction += HOU_Speed;
		}
		else if (HOU_Direction < 90) {
			HOU_Direction -= HOU_Speed;
			if (HOU_Direction <= 0) {
				HOU_Direction = 359;
			}
		}
		if (HOU_Direction < 360 && HOU_Direction >270) {
			HOU_Direction -= HOU_Speed;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) {
		if (HOU_Direction > 180) {
			HOU_Direction -= HOU_Speed;
		}
		if (HOU_Direction < 180) {
			HOU_Direction += HOU_Speed;
		}
	}

	if (!Throwing) {
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
			App->particles->AddParticle(App->particles->HOU_Shot, HOU_position.x + 9, HOU_position.y, COLLIDER_PLAYER_SHOT);

			Charging_Sound_HOU = true;
		}
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT) {
			HOU_Charge++;
			if (HOU_Charge > 9) {
				charging = true;
				//BLUE CHARGING BALL
				if (current_animation == &Blue_HOU_Front){
				App->render->Blit(Charge_texture, HOU_position.x - 14, HOU_position.y - 15, &blueball_charging.GetCurrentFrame()); }
			
				if (current_animation == &Blue_HOU_Front_Up_Down) {
					App->render->Blit(Charge_texture, HOU_position.x - 14, HOU_position.y - 14, &blueball_charging.GetCurrentFrame());
				}

				
				 if (current_animation == &Blue_HOU_Front_Up) {
					 App->render->Blit(Charge_texture, HOU_position.x - 14, HOU_position.y - 10, &blueball_charging.GetCurrentFrame());
				 }
				
				 if (current_animation == &Blue_HOU_Front_Up_Up) {
					 App->render->Blit(Charge_texture, HOU_position.x - 14, HOU_position.y - 8, &blueball_charging.GetCurrentFrame());
				 }
			
				 if (current_animation == &Blue_HOU_Front_Down_Up) {
					 App->render->Blit(Charge_texture, HOU_position.x - 14, HOU_position.y - 15, &blueball_charging.GetCurrentFrame());
				 }
				
				 if (current_animation == &Blue_HOU_Front_Down) {
					 App->render->Blit(Charge_texture, HOU_position.x - 14, HOU_position.y - 15, &blueball_charging.GetCurrentFrame());
				 }
				
				 if (current_animation == &Blue_HOU_Front_Down_Down) {
					 App->render->Blit(Charge_texture, HOU_position.x - 14, HOU_position.y - 15, &blueball_charging.GetCurrentFrame());
				 }
			
				 if (current_animation == &Blue_HOU_Back) {
					 App->render->Blit(Charge_texture, HOU_position.x - 8, HOU_position.y - 15, &blueball_charging.GetCurrentFrame());
				 }
				
				if (current_animation == &Blue_HOU_Back_Up_Up) {
					App->render->Blit(Charge_texture, HOU_position.x - 13, HOU_position.y - 8, &blueball_charging.GetCurrentFrame());
				}

				if (current_animation == &Blue_HOU_Back_UP) {
					App->render->Blit(Charge_texture, HOU_position.x - 9, HOU_position.y - 10, &blueball_charging.GetCurrentFrame());
				}
		
				if (current_animation == &Blue_HOU_Back_Up_Down) {
					App->render->Blit(Charge_texture, HOU_position.x - 8, HOU_position.y - 14, &blueball_charging.GetCurrentFrame());
				}
			
				if (current_animation == &Blue_HOU_Back_Down_Down) {
					App->render->Blit(Charge_texture, HOU_position.x - 13, HOU_position.y - 15, &blueball_charging.GetCurrentFrame());
				}
			
				if (current_animation == &Blue_HOU_Back_Down) {
					App->render->Blit(Charge_texture, HOU_position.x - 9, HOU_position.y - 15, &blueball_charging.GetCurrentFrame());
				}
				Blue_HOU_Back_Down_Up;
				if (current_animation == &Blue_HOU_Back_Down_Up) {
					App->render->Blit(Charge_texture, HOU_position.x - 8, HOU_position.y - 15, &blueball_charging.GetCurrentFrame());
				}
			
				if (current_animation == &Blue_HOU_Down) {
					App->render->Blit(Charge_texture, HOU_position.x - 14, HOU_position.y - 15, &blueball_charging.GetCurrentFrame());
				}
				
				if (current_animation == &Blue_HOU_UP) {
					App->render->Blit(Charge_texture, HOU_position.x - 14, HOU_position.y - 9, &blueball_charging.GetCurrentFrame());
				}
				//RED CHARGING BALL
				if (current_animation == &Red_HOU_Front) {
					App->render->Blit(Charge_texture, HOU_position.x - 14, HOU_position.y - 15, &Redball_charging.GetCurrentFrame());
				}

				if (current_animation == &Red_HOU_Front_Up_Down) {
					App->render->Blit(Charge_texture, HOU_position.x - 14, HOU_position.y - 14, &Redball_charging.GetCurrentFrame());
				}


				if (current_animation == &Red_HOU_Front_Up) {
					App->render->Blit(Charge_texture, HOU_position.x - 14, HOU_position.y - 10, &Redball_charging.GetCurrentFrame());
				}

				if (current_animation == &Red_HOU_Front_Up_Up) {
					App->render->Blit(Charge_texture, HOU_position.x - 14, HOU_position.y - 8, &Redball_charging.GetCurrentFrame());
				}

				if (current_animation == &Red_HOU_Front_Down_Up) {
					App->render->Blit(Charge_texture, HOU_position.x - 14, HOU_position.y - 15, &Redball_charging.GetCurrentFrame());
				}

				if (current_animation == &Red_HOU_Front_Down) {
					App->render->Blit(Charge_texture, HOU_position.x - 14, HOU_position.y - 15, &Redball_charging.GetCurrentFrame());
				}

				if (current_animation == &Red_HOU_Front_Down_Down) {
					App->render->Blit(Charge_texture, HOU_position.x - 14, HOU_position.y - 15, &Redball_charging.GetCurrentFrame());
				}

				if (current_animation == &Red_HOU_Back) {
					App->render->Blit(Charge_texture, HOU_position.x - 8, HOU_position.y - 15, &Redball_charging.GetCurrentFrame());
				}

				if (current_animation == &Red_HOU_Back_Up_Up) {
					App->render->Blit(Charge_texture, HOU_position.x - 13, HOU_position.y - 8, &Redball_charging.GetCurrentFrame());
				}

				if (current_animation == &Red_HOU_Back_UP) {
					App->render->Blit(Charge_texture, HOU_position.x - 9, HOU_position.y - 10, &Redball_charging.GetCurrentFrame());
				}

				if (current_animation == &Red_HOU_Back_Up_Down) {
					App->render->Blit(Charge_texture, HOU_position.x - 8, HOU_position.y - 14, &Redball_charging.GetCurrentFrame());
				}

				if (current_animation == &Red_HOU_Back_Down_Down) {
					App->render->Blit(Charge_texture, HOU_position.x - 13, HOU_position.y - 15, &Redball_charging.GetCurrentFrame());
				}

				if (current_animation == &Red_HOU_Back_Down) {
					App->render->Blit(Charge_texture, HOU_position.x - 9, HOU_position.y - 15, &Redball_charging.GetCurrentFrame());
				}
				Red_HOU_Back_Down_Up;
				if (current_animation == &Red_HOU_Back_Down_Up) {
					App->render->Blit(Charge_texture, HOU_position.x - 8, HOU_position.y - 15, &Redball_charging.GetCurrentFrame());
				}

				if (current_animation == &Red_HOU_Down) {
					App->render->Blit(Charge_texture, HOU_position.x - 14, HOU_position.y - 15, &Redball_charging.GetCurrentFrame());
				}

				if (current_animation == &Red_HOU_UP) {
					App->render->Blit(Charge_texture, HOU_position.x - 14, HOU_position.y - 9, &Redball_charging.GetCurrentFrame());
				}

				if (Charging_Sound_HOU) {
					Mix_PlayChannel(2, ChargeHOUSound, 0);

				}
				if (timeSoundCharge = SDL_GetTicks() + 2000) {
					Charging_Sound_HOU = false;
				}
			}
		}


		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_UP) {

			HOU_Charge = 0;
			Mix_FadeOutChannel(2, 400); //fading out channel

		}
	}
}