#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleSceneLvl1.h"
#include "ModuleSound.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMainMenu.h"
#include "ModuleSceneLvl2.h"
#include "ModuleGameOver.h"
#include "ModuleStageClear.h"



ModuleMainMenu::ModuleMainMenu()
{
	Background.x = 0;
	Background.y = 0;
	Background.w = SCREEN_WIDTH;
	Background.h = SCREEN_HEIGHT;
}


ModuleMainMenu::~ModuleMainMenu()
{
}

bool ModuleMainMenu::Start() {

	if (IsEnabled()) {
		App->player->Disable();
	}
	LOG("Loading Main Menu");

	graphics_Background = App->textures->Load("Images/Main_Menu/Last_Resort_Intro.png");
	Main_Menu = App->sound->LoadMusic("Audio/Main_Menu/Title.ogg");
	
	Mix_Volume(-1, VOLUME_MUSIC);
	Mix_PlayMusic(Main_Menu, 0);
	
	return true;
}

bool ModuleMainMenu::CleanUp() {

	LOG("Unloading Main Menu");
	App->textures->Unload(graphics_Background);
	return true;
}

update_status ModuleMainMenu::Update() {

	App->render->Blit(graphics_Background, 0, 0, &Background, 0);
	
	if (App->input->keyboard[SDL_SCANCODE_4]) {
		App->fade->FadeToBlack(App->menu, App->gameover, 3.0f);
	}
	if (App->input->keyboard[SDL_SCANCODE_2]) {
		App->fade->FadeToBlack(App->menu, App->scene1background, 3.0f);
	}
	if (App->input->keyboard[SDL_SCANCODE_3]) {
		App->fade->FadeToBlack(App->menu, App->scene2background, 3.0f);
	}
	//if (App->input->keyboard[SDL_SCANCODE_5]) {
	//	App->fade->FadeToBlack(App->menu, App->stageclear);
	//}

	return UPDATE_CONTINUE;
}