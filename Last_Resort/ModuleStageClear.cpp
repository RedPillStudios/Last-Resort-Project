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
#include "ModuleMainMenu.h"
#include "ModuleGameOver.h"
#include "ModuleParticles.h"
#include "ModulePlayer2.h"
#include "ModuleFonts.h"

#include <stdio.h>

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
	fontend = App->fonts->Load("Images/Fonts/Font_score.png", "0123456789ABCDEFGHIJKLMNPQRSTUVWXYZ_.,[]&$", 2);

	Mix_PlayMusic(StageClear, 0);
	return true;
}

bool ModuleStageClear::CleanUp() {
	
	LOG("Unloading Stage Clear images");
	App->textures->Unload(graphics_StageClearImage);
	App->fonts->UnLoad(fontend);
	return true;
}

update_status ModuleStageClear::Update() {

	//Draw everything
	App->render->Blit(graphics_StageClearImage, 220,(SCREEN_HEIGHT/2) - 50, &FirstPlaneImage);

	SumScore = Score1 + Score2;

	sprintf_s(Score1_text, "%d", Score1);
	sprintf_s(Score2_text, "%d", Score2);
	sprintf_s(SumScore_text, "%d", SumScore);

	App->fonts->BlitText((SCREEN_WIDTH / 2) - 5, (SCREEN_HEIGHT / 2) + 10, fontend, "PLAYER");
	App->fonts->BlitText((SCREEN_WIDTH / 2) + 44, (SCREEN_HEIGHT / 2) + 10, fontend, "1");
	App->fonts->BlitText((SCREEN_WIDTH / 2) + 52, (SCREEN_HEIGHT / 2) + 10, fontend, "SC0RE");
	App->fonts->BlitText((SCREEN_WIDTH / 2) + 100, (SCREEN_HEIGHT / 2) + 10, fontend, Score1_text);

	App->fonts->BlitText((SCREEN_WIDTH / 2) - 5, (SCREEN_HEIGHT / 2), fontend, "PLAYER");
	App->fonts->BlitText((SCREEN_WIDTH / 2) + 44, (SCREEN_HEIGHT / 2), fontend, "2");
	App->fonts->BlitText((SCREEN_WIDTH / 2) + 52, (SCREEN_HEIGHT / 2), fontend, "SC0RE");
	App->fonts->BlitText((SCREEN_WIDTH / 2) + 100, (SCREEN_HEIGHT / 2), fontend, Score2_text);

	App->fonts->BlitText((SCREEN_WIDTH / 2) - 5, (SCREEN_HEIGHT / 2) - 10, fontend, "SC0RE");
	App->fonts->BlitText((SCREEN_WIDTH / 2) + 44, (SCREEN_HEIGHT / 2) - 10, fontend, "SUM");
	App->fonts->BlitText((SCREEN_WIDTH / 2) + 77, (SCREEN_HEIGHT / 2) - 10, fontend, SumScore_text);

	if (App->input->keyboard[SDL_SCANCODE_SPACE]) {
		App->fade->FadeToBlack(App->stageclear, App->menu, 3.0f);
	}

	return UPDATE_CONTINUE;
}
