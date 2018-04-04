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



ModuleMainMenu::ModuleMainMenu()
{
	Background.x = 0;
	Background.y = 0;
	Background.w = 4407; //works
	Background.h = 238;
}


ModuleMainMenu::~ModuleMainMenu()
{
}

bool ModuleMainMenu::Start() {

	LOG("Loading Main Menu");

	graphics_Background = App->textures->Load("Images/Main_Menu/ScreenMenu.png");

	Main_Menu = App->sound->LoadMusic("Audio/Main_Menu/Title.ogg");
	Mix_PlayMusic(Main_Menu, -1);
	Mix_Volume(-1, MIX_MAX_VOLUME / 9);
	
	return true;
}

bool ModuleMainMenu::CleanUp() {

	LOG("Unloading Main Menu");
	App->textures->Unload(graphics_Background);
	return true;
}

update_status ModuleMainMenu::Update() {

	App->render->Blit(graphics_Background, 0, 0, &Background, 0);
	
	if (App->input->keyboard[SDL_SCANCODE_SPACE]) {

		App->fade->FadeToBlack(App->menu, App->scene1background);
	}

	return UPDATE_CONTINUE;
}