#include "ModuleStageClear.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleSceneLvl1.h"
#include "ModuleSound.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneLvl2.h"
#include "ModuleMainMenu.h"
#include "ModuleGameOver.h"
#include "ModuleParticles.h"

ModuleStageClear::ModuleStageClear() {

	//StageClearImage
	FirstPlaneImage.x = 0;
	FirstPlaneImage.y = 32;
	FirstPlaneImage.w = 212;
	FirstPlaneImage.h = 16;
}

ModuleStageClear::~ModuleStageClear() {}

bool ModuleStageClear::Start() {

	LOG("Loading Stage Clear images");
	
	//Music Here
	if (IsEnabled()) {
		if (App->player->IsEnabled() == true) {
			App->player->Disable();
			App->particles->Disable();
			
		}
	/*	if (App->player2->IsEnabled() == true) {
			App->player->Disable();
			App->particles->Disable();

		}*/
	}

	graphics_StageClearImage = App->textures->Load("Images/Stage_Clear/All_Stage_Clears.png"); 
	StageClear = App->sound->LoadMusic("Audio/Stage_Clear/Stage_Clear.ogg");

	Mix_PlayMusic(StageClear, 0);
	return true;
}

bool ModuleStageClear::CleanUp() {
	
	LOG("Unloading Stage Clear images");
	App->textures->Unload(graphics_StageClearImage);
	return true;
}

update_status ModuleStageClear::Update() {

	//Draw everything
	App->render->Blit(graphics_StageClearImage, (SCREEN_WIDTH/2) - 106,(SCREEN_HEIGHT/2) - 8 , &FirstPlaneImage);

	if (App->input->keyboard[SDL_SCANCODE_SPACE]) {
		App->fade->FadeToBlack(App->stageclear, App->menu, 3.0f);
	}

	return UPDATE_CONTINUE;
}
