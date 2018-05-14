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
#include "ModuleUI.h"


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
		if (App->player2->IsEnabled() == true) 
			App->player2->Disable();
	}

	graphics_StageClearImage = App->textures->Load("Images/Stage_Clear/All_Stage_Clears.png"); 
	fontend = App->fonts->LoadFont("Images/Fonts/Font_score.png", "0123456789ABCDEFGHIJKLMNPQRSTUVWXYZ_.,[]&$", 2);

	StageClear = App->sound->LoadMusic("Audio/Stage_Clear/Stage_Clear.ogg");

	Mix_PlayMusic(StageClear, 0);
	return true;
}

bool ModuleStageClear::CleanUp() {
	
	LOG("Unloading Stage Clear images");
	App->textures->Unload(graphics_StageClearImage);
	App->fonts->UnLoadFont(fontend);

	App->sound->UnloadMusic(StageClear);
	return true;
}

update_status ModuleStageClear::Update() {

	//Draw everything
	App->render->Blit(graphics_StageClearImage, (SCREEN_WIDTH/2) - 106,(SCREEN_HEIGHT/2) - 40, &FirstPlaneImage, 0.0f, false);

	sprintf_s(Score1_text, "%d", App->fonts->ScoreP1);
	sprintf_s(Score2_text, "%d", App->fonts->ScoreP2);
	
	SumScore = App->fonts->ScoreP1 + App->fonts->ScoreP2;

	sprintf_s(SumScore_text, "%d", SumScore);

	App->fonts->BlitText((SCREEN_WIDTH / 2) - 56, (SCREEN_HEIGHT / 2) - 14, fontend, "PLAYER");
	App->fonts->BlitText((SCREEN_WIDTH / 2) - 6, (SCREEN_HEIGHT / 2) - 14, fontend, "1");
	App->fonts->BlitText((SCREEN_WIDTH / 2) + 4, (SCREEN_HEIGHT / 2) - 14, fontend, "SC0RE");
	App->fonts->BlitText((SCREEN_WIDTH / 2) + 48, (SCREEN_HEIGHT / 2) - 14, fontend, Score1_text);

	App->fonts->BlitText((SCREEN_WIDTH / 2) - 56, (SCREEN_HEIGHT / 2) - 4, fontend, "PLAYER");
	App->fonts->BlitText((SCREEN_WIDTH / 2) - 6, (SCREEN_HEIGHT / 2) - 4, fontend, "2");
	App->fonts->BlitText((SCREEN_WIDTH / 2) + 4, (SCREEN_HEIGHT / 2) - 4, fontend, "SC0RE");
	App->fonts->BlitText((SCREEN_WIDTH / 2) + 48, (SCREEN_HEIGHT / 2) - 4, fontend, Score2_text);

	App->fonts->BlitText((SCREEN_WIDTH / 2) - 38, (SCREEN_HEIGHT / 2) + 14, fontend, "SC0RE");
	App->fonts->BlitText((SCREEN_WIDTH / 2) + 4, (SCREEN_HEIGHT / 2) + 14, fontend, "SUM");
	App->fonts->BlitText((SCREEN_WIDTH / 2) + 48, (SCREEN_HEIGHT / 2) + 14, fontend, SumScore_text);

	if (App->input->keyboard[SDL_SCANCODE_SPACE]) 
		App->fade->FadeToBlack(App->stageclear, App->menu, 3.0f);
	

	return UPDATE_CONTINUE;
}
