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

	Appear.PushBack({ 0,118,111,1 });
	Appear.PushBack({ 6,121,105,2 });
	Appear.PushBack({ 1,124,76,4 });
	Appear.PushBack({ 0,128,74,7 });
	Appear.PushBack({ 0,135,64,25 });
	Appear.PushBack({ 0,160,64,25 });
	Appear.PushBack({ 0,185,64,25 });
	Appear.PushBack({ 0,210,64,25 });
	Appear.PushBack({ 64,135,64,25 });
	Appear.PushBack({ 64,160,64,25 });
	Appear.PushBack({ 64,185,64,25 });
	Appear.PushBack({ 64,210,64,25 });
	Appear.PushBack({ 156,139, 36,19 });
	Appear.PushBack({ 160,158,36,19 });
	Appear.speed = 0.20f;
	Appear.loop = false;

	int a = 110, b = 101;
	for (int i = 18; i >= 0; --i) {
		DestroyShip.PushBack({ a,b,55,16 });
		b -= 16;
		if (b <= 17) {
			b = 101;
			a = -55;
		}
	}
	
}

ModulePlayer2::~ModulePlayer2() {}

// Load assets
bool ModulePlayer2::Start() {

	LOG("Loading player textures");

	graphics = App->textures->Load("Images/Player/Ship&Ball_Sprite.png"); // arcade version
	Shot_Sound = App->sound->LoadChunk("Audio/Shot_Sound.wav");
	
	Ship2Collider = App->collision->AddCollider({ 64,0,32,12 }, COLLIDER_PLAYER, this);


	AppearAnim = true;

	return true;
}

bool ModulePlayer2::CleanUp() {

	LOG("Cleaning Up Player Module");
	App->textures->Unload(graphics);

	App->powerup->Disable();

	return true;
}

// Update: draw background
update_status ModulePlayer2::Update() {

	if (AppearAnim) {

		current_animation2 = &Appear;
		AppearAnim = false;
	}

	if (!AppearAnim && current_animation2->Finished()) {
		current_animation2 = &Standard;
	}

	int passedframes;
	int speed = 3;

	if (startAnim) {

		if (current_animation2->getCurrentFrame() >= 13) {
			startAnim = false;
		}
	}

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

		App->particles->AddParticle(App->particles->Laser, setFirePos2().x, setFirePos2().y);
		App->particles->AddParticle(App->particles->ShootExplosion, setFirePos2().x, setFirePos2().y);
		Mix_PlayChannel(-1, Shot_Sound, 0);
	}

	/* Draw everything --------------------------------------*/
	Ship2 = current_animation2->GetCurrentFrame();
	Ship2Collider->SetPos(positionp2.x, positionp2.y);
	App->render->Blit(graphics, positionp2.x, positionp2.y, &Ship2, 0.0f);

	return UPDATE_CONTINUE;
}

void ModulePlayer2::OnCollision(Collider *c1, Collider *c2) {

	if (((c1->type == COLLIDER_TYPE::COLLIDER_ENEMY || c1->type == COLLIDER_TYPE::COLLIDER_WALL) && c2->type == COLLIDER_PLAYER) || ((c2->type == COLLIDER_TYPE::COLLIDER_ENEMY || c2->type == COLLIDER_TYPE::COLLIDER_WALL) && c1->type == COLLIDER_PLAYER)) {
		Ship2Collider->to_delete = true;
	  	current_animation2 = &DestroyShip;
	
		if (current_animation2->Finished()) {
			App->player2->Disable();
			App->player->pressed = false;
		
		}
	}

}