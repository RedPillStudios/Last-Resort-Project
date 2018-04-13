#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleSound.h"
#include "ModuleFadeToBlack.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{

	position.x = 20;
	position.y = SCREEN_HEIGHT/2;

	positionp2.x = 20;
	positionp2.y = SCREEN_HEIGHT / 4;

	Standard.PushBack({64,0,32,12});

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

ModulePlayer::~ModulePlayer() {}

// Load assets
bool ModulePlayer::Start() {

	LOG("Loading player textures");
	
	if (App->particles->IsEnabled() == false)
		App->particles->Enable();

	if (IsEnabled())
		App->collision->Enable();
	
	graphics = App->textures->Load("Images/Player/Ship&Ball_Sprite.png"); // arcade version
	Shot_Sound = App->sound->LoadChunk("Audio/Shot_Sound.wav");

	Ship1Collider = App->collision->AddCollider({ 64,0,32,12 }, COLLIDER_PLAYER, this);
	Ship2Collider = App->collision->AddCollider({ 64,0,32,12 }, COLLIDER_PLAYER, this);
	
	
	AppearAnim = true;


	return true;
}

bool ModulePlayer::CleanUp() {

	LOG("Cleaning Up Player Module");
	App->collision->Disable();
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModulePlayer::Update() {

	
	if (AppearAnim) {
		current_animation = &Appear;
		current_animation2 = &Appear;
		AppearAnim = false;
	}
	if (!AppearAnim && current_animation->Finished() && current_animation2->Finished()) {

		current_animation = &Standard;
		current_animation2 = &Standard;
	}

	int passedframes;
	int speed = 3;

	if (startAnim) {
		
		if(current_animation->getCurrentFrame()>=13){
			startAnim = false;
		}
		if (current_animation2->getCurrentFrame() >= 13) {
			startAnim = false;
		}
	}

	//Movement Up
	if(App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) {
		current_animation = &Up;
		position.y -= speed;
		while (position.y <= 2) {
			position.y = 2;
			break;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT) {
		current_animation2 = &Up;
		positionp2.y -= speed;
		while (positionp2.y <= 2) {
			positionp2.y = 2;
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
	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT) {
		current_animation2 = &Down;
		positionp2.y += speed;
		while (positionp2.y >= SCREEN_HEIGHT - 15) {
			positionp2.y = SCREEN_HEIGHT - 15;
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
	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT) {
		positionp2.x += speed;
		while (positionp2.x >= SCREEN_WIDTH - 30) {
			positionp2.x = SCREEN_WIDTH - 30;
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
	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT) {
		positionp2.x -= speed;
		while (positionp2.x <= 2) {
			positionp2.x = 2;
			break;
		}
	}
	//Shoot
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {

		App->particles->AddParticle(App->particles->Laser, setFirePos().x, setFirePos().y);
		App->particles->AddParticle(App->particles->ShootExplosion, setFirePos().x, setFirePos().y);
		Mix_PlayChannel(-1, Shot_Sound, 0);
	}
	if (App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_DOWN) {

		App->particles->AddParticle(App->particles->Laser, setFirePos2().x, setFirePos2().y);
		App->particles->AddParticle(App->particles->ShootExplosion, setFirePos2().x, setFirePos2().y);
		Mix_PlayChannel(-1, Shot_Sound, 0);
	}
	
	// Draw everything --------------------------------------
	Ship2 = current_animation2->GetCurrentFrame();
	Ship = current_animation->GetCurrentFrame();

	Ship1Collider->SetPos(position.x, position.y);
	Ship2Collider->SetPos(positionp2.x, positionp2.y);
	
	App->render->Blit(graphics, position.x, position.y,&Ship,0.0f);
	App->render->Blit(graphics, positionp2.x, positionp2.y, &Ship2, 0.0f);
	
	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider *c1, Collider *c2) {
	
	current_animation = &DestroyShip;
	if (current_animation->Finished()) {
		App->player->Disable();
		App->fade->FadeToBlack((Module*)App->scene1background, (Module*)App->gameover, 1.0f); //scene1 must be changed!!
	}
}