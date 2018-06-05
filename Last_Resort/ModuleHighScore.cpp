#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "ModuleGameOver.h"
#include "ModuleSound.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMainMenu.h"
#include "ModuleSceneLvl1.h"
#include "ModuleStageClear.h"
#include "ModuleUI.h"
#include "ModuleHighScore.h"

#include <stdio.h>

ModuleHighScore::ModuleHighScore()
{

	Background.x = 0;
	Background.y = 0;
	Background.w = SCREEN_WIDTH;
	Background.h = SCREEN_HEIGHT;


	ScoreRect.x = 0;
	ScoreRect.y = 0;
	ScoreRect.w = 1920;
	ScoreRect.h = 1080;

}


ModuleHighScore::~ModuleHighScore()
{
}

bool ModuleHighScore::Start() {

	LOG("Loading Game Over Screen");
	Background_HighScoreImage = App->textures->Load("Images/Highscores/HighscoreScreen_Sprite.png");
	HighScore = App->textures->Load("Images/Highscores/HigscoreFont_Sprite.png");

	fontend = App->fonts->LoadFont("Images/Fonts/Font_score.png", "0123456789ABCDEFGHIJKLMNPQRSTUVWXYZ_.,[]&$", 2);

	Mix_PlayMusic(GameOver, 0);

	if (IsEnabled()) {
		if (App->player->IsEnabled())
			App->player->Disable();
		if (App->player2->IsEnabled())
			App->player2->Disable();
	}
	if (App->scene1background->IsEnabled()) {
		App->scene1background->Disable();
	}
	return true;
}

bool ModuleHighScore::CleanUp() {

	LOG("Unloading Game Over Screen");
	//App->fonts->Disable();
	App->textures->Unload(Background_HighScoreImage);
	App->textures->Unload(HighScore);
	App->fonts->UnLoadFont(fontend);

	App->sound->UnloadMusic(GameOver);

	return true;
}

update_status ModuleHighScore::Update() {

	App->render->Blit(Background_HighScoreImage, 0, 0, &Background, 0);
	App->render->Blit(HighScore, 0, 0, &Background, 0);
	if (App->fonts->ccompleted == true) {

		App->fonts->BlitRanking(App->fonts->ranking);

		if (RankBlitted == true) {
			if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
				App->fade->FadeToBlack(App->HighScore, App->menu, 1.0f);
			}
		}
	}
	

	return UPDATE_CONTINUE;
}