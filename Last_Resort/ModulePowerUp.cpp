#include "Application.h"
#include "ModulePowerUp.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleInput.h"
#include <math.h>

#define SPAWN_MARGIN 50

powerUp_red::powerUp_red(int x, int y) : powerUp(x, y) {

	powerUp::sprite = App->textures->Load("Images/General/PowerUps_Sprite.png");
	Red.PushBack({ 49,64,31,16 });
	Red.PushBack({ 18,64,31,16 });
	collider = App->collision->AddCollider({ 500,120,31,16 }, COLLIDER_TYPE::COLLIDER_POWER_UP, (Module*)App->powerup);
	animation = &Red;
	Red.speed = 0.1f;
	type = POWERUP_TYPES::RED;

};

powerUp_Laser::powerUp_Laser(int x, int y) : powerUp(x, y) {

	powerUp::sprite = App->textures->Load("Images/General/PowerUps_Sprite.png");
	ChangeColor.PushBack({ 49,80,31,16 });
	ChangeColor.PushBack({ 18,80,31,16 });
	collider = App->collision->AddCollider({ 500,120,31,16 }, COLLIDER_TYPE::COLLIDER_POWER_UP, (Module*)App->powerup);
	animation = &ChangeColor;
	ChangeColor.speed = 0.1f;
	type = POWERUP_TYPES::LASER;
};


ModulePowerUp::ModulePowerUp() {

	for (uint i = 0; i < MAX_POWERUP; ++i)
		PowerUps[i] = nullptr;
	int counter = 0;


	for (uint i = 0; i <= 7; ++i) {
		HOU_Front_Up_Up.PushBack({ 261,counter,17,23 });
		counter += 23;
		if (counter >= 184)
			counter = 0;
	}
	HOU_Front_Up_Up.speed = 0.4f;

	for (uint i = 0; i <= 7; ++i) {
		HOU_Front_Up_Down.PushBack({ 218,counter,22,17 });
		counter += 17;
		if (counter >= 136 )
			counter = 0;
	}
	HOU_Front_Up_Down.speed = 0.4f;

	for (uint i = 0; i <= 7; ++i) {
		HOU_Front_Down_Up.PushBack({ 490,counter,22,17 });
		counter += 17;
		if (counter >= 136)
			counter = 0;
	}
	HOU_Front_Down_Up.speed = 0.4f;

	for (uint i = 0; i <= 7; ++i) {
		HOU_Front_Down_Down.PushBack({ 452,counter,17,23 });
		counter += 23;
		if (counter >= 184)
			counter = 0;
	}
	HOU_Front_Down_Down.speed = 0.4f;

	

	for (uint i = 0; i <= 7; ++i) {
		HOU_Front_Up.PushBack({ 240,counter,21,21 });
		counter += 21;
		if (counter >= 168)
			counter = 0;
	}

	HOU_Front_Up.speed = 0.4f;

	for (uint i = 0; i <= 7; i++) {
		HOU_Front_Down.PushBack({ 469,counter,21,21 });
		counter += 21;
		if (counter >= 168)
			counter = 0;
	}
	HOU_Front_Down.speed = 0.4f;

	for (uint i = 0; i <= 7; ++i) {
		HOU_Back_Up_Up.PushBack({ 294,counter,17,23 });
		counter += 23;
		if (counter >= 184)
			counter = 0;
	}
	HOU_Back_Up_Up.speed = 0.4f;

	for (uint i = 0; i <= 7; ++i) {
		HOU_Back_Up_Down.PushBack({ 332,counter,22,17 });
		counter += 17;
		if (counter >= 136)
			counter = 0;
	}
	HOU_Back_Up_Down.speed = 0.4f;

	for (uint i = 0; i <= 7; ++i) {
		HOU_Back_Down_Up.PushBack({ 376,counter,22,17 });
		counter += 17;
		if (counter >= 136)
			counter = 0;
	}
	HOU_Back_Down_Up.speed = 0.4f;

	for (uint i = 0; i <= 7; ++i) {
		HOU_Back_Down_Down.PushBack({ 419,counter,17,23 });
		counter += 23;
		if (counter >= 184)
			counter = 0;
	}
	HOU_Back_Down_Down.speed = 0.4f;

	for (uint i = 0; i <= 7; i++) {
		HOU_Back_Down.PushBack({ 398,counter,21,21 });
		counter += 21;
		if (counter >= 168)
			counter = 0;
	}
	HOU_Back_Down.speed = 0.4f;


	for (uint i = 0; i <= 7; i++) {
		HOU_Back_UP.PushBack({ 311,counter,21,21 });
		counter += 21;
		if (counter >= 168)
			counter = 0;
	}
	HOU_Back_UP.speed = 0.4f;

	Throw_Ball.PushBack({140,178,26,26});
	Throw_Ball.PushBack({ 140,204,26,26 });
	Throw_Ball.PushBack({ 141,230,26,26 });
	Throw_Ball.PushBack({ 141,256,26,26 });
	Throw_Ball.PushBack({ 140,282,26,26 });
	Throw_Ball.PushBack({ 139,308,26,26 });
	Throw_Ball.speed = 0.2f;

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

	Charge.PushBack({ 0,0,47,47 });
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

	//HOU_position_x = App->player->position.x;
	//HOU_position_y = App->player->position.y;

	LOG("Loading PowerUps");
	if (App->player->IsEnabled() == true && App->powerup->IsEnabled() == false)
		App->powerup->Enable();

	PickUpSpeed = App->sound->LoadChunk("Audio/General/005_PowerUpSpeed.wav");
	PickUpWeapon = App->sound->LoadChunk("Audio/General/006_PowerUpWeapon.wav");

	ChargeHOUSound = App->sound->LoadChunk("Audio/General/Charging_shot.wav");
	ReleasedChargeHOUSound = App->sound->LoadChunk("Audio/General/Releasing_charged_shot.wav");

	HOU_Texture = App->textures->Load("Images/Player/Ship&Ball_Sprite.png");
	Charge_texture = App->textures->Load("Images/Player/Charge_Ball.png");
	
	Mix_VolumeChunk(ReleasedChargeHOUSound, MIX_MAX_VOLUME / 2);

	HOU_activated = false;
	fixed = false;

	current_animation = &HOU_Front;
	Charge_animation = &Charge;
	colliderHUB = App->collision->AddCollider({ -2000,-200,22,16 }, COLLIDER_HOU, this);

	
	return true;
}

bool ModulePowerUp::CleanUp() {

	LOG("Cleaning Up Power Ups");
	App->textures->Unload(HOU_Texture);
	App->textures->Unload(Charge_texture);
	for (uint i = 0; i < MAX_POWERUP; ++i) {
		if (PowerUps[i] != nullptr) {
			App->textures->Unload(PowerUps[i]->sprite);
			PowerUps[i]->collider->to_delete = true;
			PowerUps[i]->animation = nullptr;

			delete PowerUps[i];
			PowerUps[i] = nullptr;
			
		}

		queue[i].type = NON;

	}
	if (colliderHUB != nullptr) {
		colliderHUB = nullptr;
	}
	if (current_animation != nullptr) {
		current_animation = nullptr;
	}

	App->sound->UnloadChunks(PickUpSpeed);
	App->sound->UnloadChunks(PickUpWeapon);
	App->sound->UnloadChunks(ChargeHOUSound);
	App->sound->UnloadChunks(ReleasedChargeHOUSound);

	return true;
}


update_status ModulePowerUp::PreUpdate() {

	for (uint i = 0; i < MAX_POWERUP; ++i) {

		if (queue[i].type != POWERUP_TYPES::NON) {

			if (queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN) {

				spawnPowerUp(queue[i]);
				queue[i].type = POWERUP_TYPES::NON;
				LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
			}
		}
	}

	return UPDATE_CONTINUE;
}


update_status ModulePowerUp::Update() {


	shipCenter.x = App->player->position.x + 10;
	shipCenter.y = App->player->position.y;
	for (uint i = 0; i < MAX_POWERUP; ++i)
		if (PowerUps[i] != nullptr)PowerUps[i]->Draw(PowerUps[i]->sprite);

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
				current_animation = &HOU_Front;
			}
			else if (HOU_Direction >= 15 && HOU_Direction < 35) {
				current_animation = &HOU_Front_Down_Up;
			}
			else if (HOU_Direction >= 35 && HOU_Direction < 55) {
				current_animation = &HOU_Front_Down;
			}
			else if (HOU_Direction >= 55 && HOU_Direction < 75) {
				current_animation = &HOU_Front_Down_Down;
			}
			else if (HOU_Direction >= 75 && HOU_Direction < 105) {
				current_animation = &HOU_Down;
			}
			else if (HOU_Direction >= 105 && HOU_Direction < 125) {
				current_animation = &HOU_Back_Down_Down;
			}
			else if (HOU_Direction >= 125 && HOU_Direction < 145) {
				current_animation = &HOU_Back_Down;
			}
			else if (HOU_Direction >= 145 && HOU_Direction < 165) {
				current_animation = &HOU_Back_Down_Up;
			}
			else if (HOU_Direction >= 165 && HOU_Direction < 195) {
				current_animation = &HOU_Back;
			}
			else if (HOU_Direction >= 195 && HOU_Direction < 215) {
				current_animation = &HOU_Back_Up_Down;
			}
			else if (HOU_Direction >= 215 && HOU_Direction < 225) {
				current_animation = &HOU_Back_UP;
			}
			else if (HOU_Direction >= 225 && HOU_Direction < 255) {
				current_animation = &HOU_Back_Up_Up;
			}
			else if (HOU_Direction >= 255 && HOU_Direction < 285) {
				current_animation = &HOU_UP;
			}
			else if (HOU_Direction >= 285 && HOU_Direction < 305) {
				current_animation = &HOU_Front_Up_Up;
			}
			else if (HOU_Direction >= 305 && HOU_Direction < 325) {
				current_animation = &HOU_Front_Up;
			}
			else if (HOU_Direction >= 325 && HOU_Direction < 345) {
				current_animation = &HOU_Front_Up_Down;
			}
			else if (HOU_Direction >= 345 && HOU_Direction <= 360) {
				current_animation = &HOU_Front;
			}


			//Settinng Grpah position HOU

			HOU_position.x = shipCenter.x + 40 * cos(HOU_Direction*PI / 180);
			HOU_position.y = shipCenter.y + 30 * sin(HOU_Direction*PI / 180);

		}
		//Render HOU
		if (Throwing) {
			Animation* Sup = current_animation;
			current_animation = &Throw_Ball;
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

void ModulePowerUp::OnCollision(Collider *c1, Collider *c2) {

	for (uint i = 0; i < MAX_POWERUP; ++i) {

		if (PowerUps[i] != nullptr && PowerUps[i]->GetCollider() == c1) {
			HOU_activated = true;
			PowerUps[i]->OnCollision(c2);
			if (PowerUps[i]->type == POWERUP_TYPES::RED)
				App->player->WeaponType = 2;
			if (PowerUps[i]->type == POWERUP_TYPES::LASER)
				App->player->WeaponType = 1;
			//ADD HERE App.player.score += score;
			delete PowerUps[i];
			PowerUps[i] = nullptr;
			break;
		}
	}
}



bool ModulePowerUp::AddPowerUp(POWERUP_TYPES type, int x, int y) {

	bool ret = false;

	for (uint i = 0; i < MAX_POWERUP; ++i) {

		if (queue[i].type == POWERUP_TYPES::NON) {

			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}


void ModulePowerUp::spawnPowerUp(const PowerUpInfo &info)
{
	// find room for the new enemy
	uint i = 0;
	for (; PowerUps[i] != nullptr && i < MAX_POWERUP; ++i);

	if (i != MAX_POWERUP)
	{
		switch (info.type)
		{
		case POWERUP_TYPES::RED:
			PowerUps[i] = new powerUp_red(info.x, info.y);
			break;
		case POWERUP_TYPES::LASER:
			PowerUps[i] = new powerUp_Laser(info.x, info.y);
			break;
		}
	}
}

void ModulePowerUp::throwHOU() {
	Mix_FadeOutChannel(1, 400);//fading out channel
	Mix_PlayChannel(-1, ReleasedChargeHOUSound, 0);//releasing sound

	HOU_position.x++;
 	HOU_position.x += (10 * cos(HOU_Direction*PI / 180));
	HOU_position.y += (10 * sin(HOU_Direction*PI / 180));

}

void ModulePowerUp::returnHOU() {
	HOU_position.x = shipCenter.x-(10 * cos(HOU_Direction*PI / 180));
	HOU_position.y = shipCenter.y-(10 * sin(HOU_Direction*PI / 180));
}
void ModulePowerUp::Hou_Movement() {

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
			//Throwing = true;
			//Throw = true;
			Charging_Sound_HOU = true;
		}
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT) {
			HOU_Charge++;
			if (HOU_Charge > 9) {
				charging = true;
				App->render->Blit(Charge_texture, HOU_position.x - 10, HOU_position.y - 15, &Charge_animation->GetCurrentFrame());
				
				if (Charging_Sound_HOU) {
					Mix_PlayChannelTimed(1, ChargeHOUSound, 0, 2000);
					
				}
				if (timeSoundCharge = SDL_GetTicks() + 2000){
					Charging_Sound_HOU =false;
				}
				
			}
		}


		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_UP) {
			
			HOU_Charge = 0;
			Mix_FadeOutChannel(1,400); //fading out channel
		/*if(Charging_Sound_HOU = false)
			Mix_PlayChannel(-1, ReleasedChargeHOUSound,0);*/
		}
	}
}