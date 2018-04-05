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
#include "ModuleGameOver.h"


ModuleSceneLvl2::ModuleSceneLvl2() {

	//First Background
	Background.x = 0;
	Background.y = 0;
	Background.x = 4407;
	Background.h = 238;

	//Mid Background
	MidBackground.x = 0;
	MidBackground.y = 0;
	MidBackground.w = 1302;
	MidBackground.h = 159;

}

ModuleSceneLvl2::~ModuleSceneLvl2()
{
}


bool ModuleSceneLvl2::Start() {
	
	LOG("Loading Background Assets");

	//graphics_Background = App->textures->Load("Images/Background_Lvl2/First_Level_Background.png");
	//graphics_Mid = App->textures->Load("Images/Background_Lvl2/Mid_Level_Background.png");

	//Music
	Stage2 = App->sound->LoadMusic("Audio/Stage2/The_Ruins_Of_The_Metro.ogg");
	Mix_PlayMusic(Stage2, -1);
	Mix_Volume(-1, MIX_MAX_VOLUME / 9);

	if (App->player->IsEnabled() == false) {

		App->player->Enable();
	}
	if (App->scene2background->IsEnabled() == false) {

		App->player->Disable();
	}

	return true;
}

bool ModuleSceneLvl2::CleanUp() {

	LOG("Loading Lvl2 Scene");
	App->textures->Unload(graphics_Background);
	App->textures->Unload(graphics_Mid);

	return true;
}

update_status ModuleSceneLvl2::Update() {

	float SpeedBackground = 3;
	float SpeedMid = 2;

	if (Background_position_X < -4077) {

		Background_position_X -= SpeedBackground;
	}
	if (MidBackground_position_X < -972) {

		MidBackground_position_X -= SpeedMid;
	}

	App->render->Blit(graphics_Background, (Background_position_X) / 3.5, 0, &Background, 1.0f);
	App->render->Blit(graphics_Mid, (Background_position_X) / 3, 30, &MidBackground);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {

		App->fade->FadeToBlack(App->scene2background, App->gameover, 2.0f);
	}

	return UPDATE_CONTINUE;
}