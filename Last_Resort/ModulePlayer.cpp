#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleSound.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 20;
	position.y = SCREEN_HEIGHT/2;

	Standard.PushBack({64,0,32,12});

	Up.PushBack({ 32,0,32,13 });
	Up.PushBack({ 0,0,32,13 });
	Up.speed = 0.10f;
	Down.PushBack({96,0,32,12});
	Down.PushBack({128,1,32,11});
	Down.speed = 0.10f;
	
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
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Images/Player/Ship&Ball_Sprite.png"); // arcade version
	return ret;
}

bool ModulePlayer::CleanUp() {

	LOG("Unloading Game Over Screen");
	App->textures->Unload(graphics);

	return true;

}


// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation=&Standard;

	int speed = 2;

	if (startAnim) {
		current_animation = &Appear;
		if(current_animation->getCurrentFrame()>=13){
			startAnim = false;
		}

	}
	if (startAnim == false) {
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
		{

			current_animation = &Up;
			position.y -= (speed + 1);

		}
		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
		{
			current_animation = &Down;
			position.y += (speed + 1);
		}
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) {
			position.x += (speed + 1);
		}
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) {
			position.x -= (speed + 1);
		}
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN) {

			App->particles->AddParticle(App->particles->Laser, position.x + 35, position.y);
			//Mix_PlayChannel(-1, App->particles->LaserSound, 0);
			App->particles->AddParticle(App->particles->ShootExplosion, position.x + 30, position.y);
			App->particles->AddParticle(App->particles->ShootExplosion, position.x + 30, position.y, 25);
		}
	}

	// Draw everything --------------------------------------

	Ship = current_animation->GetCurrentFrame();
	if (startAnim) {

		App->render->Blit(graphics, position.x, position.y, &Ship);
	
	}
	else if (startAnim==false) {
		App->render->Blit(graphics, position.x, position.y, &Ship, 0.0f);
	}
	
	return UPDATE_CONTINUE;
}