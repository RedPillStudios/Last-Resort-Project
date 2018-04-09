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
	Appear.PushBack({ 0,117,111,1 });
	Appear.PushBack({ 6,117,111,1 });

	Appear.PushBack({ 1,120,76,7 });
	Appear.PushBack({ 0,123,74,3 });

	Appear.PushBack({ 2,137,64,14 });
	Appear.PushBack({ 2,167,64,14 });
	Appear.PushBack({ 0,189,51,15 });
	Appear.PushBack({ 0,215,51,15 });

	Appear.PushBack({ 64,139,64,16 });
	Appear.PushBack({ 64,160,64,24 });
	Appear.PushBack({ 71,185,57,26 });
	Appear.PushBack({ 72,56,111,24 });

	Appear.PushBack({ 155,138, 111,1 });
	Appear.PushBack({ 159,160,31,14 });

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Images/Player/Ship&Ball_Sprite.png"); // arcade version
	
	Shot_Sound = App->sound->LoadChunk("Audio/Shot_Sound.wav");
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
		if(current_animation->getCurrentFrame()==13){
			startAnim = false;
		}

	}

	if(App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
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
		position.x -= (speed+1);
	}
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN) {

		App->particles->AddParticle(App->particles->Laser, position.x + 35, position.y);
	
		App->particles->AddParticle(App->particles->ShootExplosion, position.x + 30, position.y);
		App->particles->AddParticle(App->particles->ShootExplosion, position.x + 30, position.y, 25);

		Mix_PlayChannel(-1, Shot_Sound, 0);
			
	}
	

	// Draw everything --------------------------------------

	//App->render->Blit(graphics,0,0,&Ship,1.0f);
	SDL_Rect r = current_animation->GetCurrentFrame();
	
	App->render->Blit(graphics, position.x, position.y, &r,0.0f);
	
	return UPDATE_CONTINUE;
}