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
#include "ModuleRender.h"
#include "ModuleMainMenu.h"
#include "ModuleStageClear.h"

ModuleSceneLvl2::ModuleSceneLvl2() {

	////First Background
	//Background.x = 0;
	//Background.y = 0;
	//Background.w = 3896;
	//Background.h = 224;

	////Mid Background
	//Foreground.x = 0;
	//Foreground.y = 0;
	//Foreground.w = 4825;
	//Foreground.h = 224;

}

ModuleSceneLvl2::~ModuleSceneLvl2()
{
}


bool ModuleSceneLvl2::Start() {
	//
	//LOG("Loading Background Assets");
	//graphics_Background = App->textures->Load("Images/Background_Lvl2/First_Level_Background.png");
	//graphics_Mid = App->textures->Load("Images/Background_Lvl2/Mid_Level_Background.png");

	////Music
	//Stage2 = App->sound->LoadMusic("Audio/Stage2/The_Ruins_Of_The_Metro.ogg");
	//Mix_PlayMusic(Stage2, -1);
	//Mix_Volume(-1, VOLUME_MUSIC);

	//if (IsEnabled()) {
	//	if (App->player->IsEnabled() == false) {
	//		App->player->Enable();
	//	}
	//	App->player->resetPosition();
	//}
	//if (IsEnabled() == false) {
	//	if (App->player->IsEnabled() == true) {
	//		App->player->Disable();
	//	}
	//}
	return true;
}

bool ModuleSceneLvl2::CleanUp() {

	/*LOG("Loading Lvl2 Scene");
	App->textures->Unload(graphics_Background);
	App->textures->Unload(graphics_Mid);
	Background_position_X = 0;
	Foreground_position_X = SCREEN_WIDTH * 3;
	*/
	return true;
}

update_status ModuleSceneLvl2::Update() {

	/*float SpeedBackground = 2;
	float SpeedMid = 3;


		Background_position_X -= SpeedBackground;
		Foreground_position_X -= SpeedMid;
	
	

	App->render->Blit(graphics_Background, (int)(Background_position_X / 3.5), 0, &Background, 1.0f);
	App->render->Blit(graphics_Mid, (int)(Foreground_position_X / 3), 0, &Foreground,1.0f);

	if (App->input->keyboard[SDL_SCANCODE_1]) {
		App->fade->FadeToBlack(App->scene2background, App->menu, 3.0f);
	}
	if (App->input->keyboard[SDL_SCANCODE_2]) {
		App->fade->FadeToBlack(App->scene2background, App->scene1background, 3.0f);
	}
	if (App->input->keyboard[SDL_SCANCODE_4]) {
		App->fade->FadeToBlack(App->scene2background, App->gameover, 3.0f);
	}
	if (App->input->keyboard[SDL_SCANCODE_5]) {
		App->fade->FadeToBlack(App->scene2background, App->scene1background, 3.0f);
	}
	*/
	return UPDATE_CONTINUE;
}