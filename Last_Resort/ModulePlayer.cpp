#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 20;
	position.y = SCREEN_HEIGHT/2;
	//position.x = 100;
	//position.y = 220;

	Standard.PushBack({64,0,32,12});

	Up.PushBack({ 32,0,32,13 });
	Up.PushBack({ 0,0,32,13 });

	Down.PushBack({96,0,32,12});
	Down.PushBack({128,1,32,11});
	

	
	// TODO 4: Make ryu walk backwards with the correct animations
	//App->render->Blit(graphics, 0, 0, &(backward.GetCurrentFrame()), 0.90f);
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

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation=&Standard;


	int speed = 2;

	if(App->input->keyboard[SDL_SCANCODE_W] == 1)
	{

		current_animation = &Up;
		position.y -= (speed + 1);

	}
	if (App->input->keyboard[SDL_SCANCODE_S] == 1)
	{
		current_animation = &Down;
		position.y += (speed + 1);
	}
	if (App->input->keyboard[SDL_SCANCODE_D] == 1) {
		position.x += (speed + 1);
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == 1) {
		position.x -= (speed+1);
	}
	


	// Draw everything --------------------------------------

	//App->render->Blit(graphics,0,0,&Ship,1.0f);
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y, &r,1);
	
	return UPDATE_CONTINUE;
}