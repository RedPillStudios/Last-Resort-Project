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



ModuleStageClear::ModuleStageClear() {

	//StageClearImage
	FirstPlaneImage.x = 0;
	FirstPlaneImage.y = 32;
	FirstPlaneImage.w = 212;
	FirstPlaneImage.h = 16;
}

ModuleStageClear::~ModuleStageClear() {

}

bool ModuleStageClear::Start() {

	LOG("Loading <stage clear> images");

	//here the asing of the images with paths
	graphics_StageClearImage = App->textures->Load("Images/Stage_Clear/All_Stage_Clears.png");  //name of the image changed (review othe branches to see if it gives other errors)

	//Music Here
	if (IsEnabled()) {
		if (App->player->IsEnabled() == true) {
			App->player->Disable();
		}
	}
	if (IsEnabled() == false) {
		if (App->player->IsEnabled() == false) {
			App->player->Enable();
		}
	}
	return true;
}

bool ModuleStageClear::CleanUp() {
	
	LOG("Unloading Stage Clear images");

	App->textures->Unload(graphics_StageClearImage);

	return true;
}

update_status ModuleStageClear::Update() {

	//Draw everything
	App->render->Blit(graphics_StageClearImage, SCREEN_WIDTH/4,SCREEN_HEIGHT/3 , &FirstPlaneImage);




	//change between modules

	if (App->input->keyboard[SDL_SCANCODE_1]) {
		App->fade->FadeToBlack(App->StageClear, App->menu, 3.0f);
	}
	if (App->input->keyboard[SDL_SCANCODE_4]) {

		App->fade->FadeToBlack(App->StageClear, App->gameover, 3.0f);
	}
	if (App->input->keyboard[SDL_SCANCODE_3]) {
		App->fade->FadeToBlack(App->StageClear, App->scene2background, 3.0f);
	}
	if (App->input->keyboard[SDL_SCANCODE_2]) {
		App->fade->FadeToBlack(App->StageClear, App->scene1background, 3.0f);
	}


	return UPDATE_CONTINUE;
}


