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

#include <stdio.h>

ModuleGameOver::ModuleGameOver()
{

	Background.x = 0;
	Background.y = 0;
	Background.w = SCREEN_WIDTH;
	Background.h = SCREEN_HEIGHT;

	GameOverImage.x = (SCREEN_WIDTH / 2) - 20;
	GameOverImage.y = (SCREEN_HEIGHT / 2) - 20; //20 lo he puesto random, tiene que estar en medio xD
	GameOverImage.w = 150;
	GameOverImage.h = 150; //W y H tambien random

	ScoreRect.x = 0;
	ScoreRect.y = 0;
	ScoreRect.w = 1920;
	ScoreRect.h = 1080;

}


ModuleGameOver::~ModuleGameOver()
{
}

bool ModuleGameOver::Start() {

		LOG("Loading Game Over Screen");
		graphics_GameOverImage = App->textures->Load("Images/Congrats/GameOver.png");
		fontend = App->fonts->LoadFont("Images/Fonts/Font_score.png", "0123456789ABCDEFGHIJKLMNPQRSTUVWXYZ_.,[]&$", 2);


		GameOver = App->sound->LoadMusic("Audio/Congrats/GameOver.ogg");
		
	
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
		Score = false;
		
		SubstractCoins = true;
	
	return true;
}

bool ModuleGameOver::CleanUp() {

	LOG("Unloading Game Over Screen");
	//App->fonts->Disable();
	App->textures->Unload(graphics_GameOverImage);
	App->fonts->UnLoadFont(fontend);

	App->sound->UnloadMusic(GameOver);

	return true;
}

update_status ModuleGameOver::Update() {

	App->render->Blit(graphics_GameOverImage, 0, 0, &Background, 0);

	if (App->input->keyboard[SDL_SCANCODE_LSHIFT] == KEY_STATE::KEY_DOWN || App->input->keyboard[SDL_SCANCODE_RSHIFT] == KEY_STATE::KEY_DOWN) {
		App->textures->Unload(graphics_GameOverImage);
		Score = true;
	}

	if (Score) {

		sprintf_s(Score1_text, "%d", App->fonts->ScoreP1);
		sprintf_s(Score2_text, "%d", App->fonts->ScoreP2);

		SumScore = App->fonts->ScoreP1 + App->fonts->ScoreP2;

		sprintf_s(SumScore_text, "%d", SumScore);

		App->fonts->BlitText((SCREEN_WIDTH / 2) - 54, (SCREEN_HEIGHT / 2) - 14, fontend, "PLAYER");
		App->fonts->BlitText((SCREEN_WIDTH / 2) - 4, (SCREEN_HEIGHT / 2) - 14, fontend, "1");
		App->fonts->BlitText((SCREEN_WIDTH / 2) + 6, (SCREEN_HEIGHT / 2) - 14, fontend, "SC0RE");
		App->fonts->BlitText((SCREEN_WIDTH / 2) + 50, (SCREEN_HEIGHT / 2) - 14, fontend, Score1_text);

		App->fonts->BlitText((SCREEN_WIDTH / 2) - 54, (SCREEN_HEIGHT / 2) - 4, fontend, "PLAYER");
		App->fonts->BlitText((SCREEN_WIDTH / 2) - 4, (SCREEN_HEIGHT / 2) - 4, fontend, "2");
		App->fonts->BlitText((SCREEN_WIDTH / 2) + 6, (SCREEN_HEIGHT / 2) - 4, fontend, "SC0RE");
		App->fonts->BlitText((SCREEN_WIDTH / 2) + 50, (SCREEN_HEIGHT / 2) - 4, fontend, Score2_text);

		App->fonts->BlitText((SCREEN_WIDTH / 2) - 36, (SCREEN_HEIGHT / 2) + 14, fontend, "SC0RE");
		App->fonts->BlitText((SCREEN_WIDTH / 2) + 6, (SCREEN_HEIGHT / 2) + 14, fontend, "SUM");
		App->fonts->BlitText((SCREEN_WIDTH / 2) + 50, (SCREEN_HEIGHT / 2) + 14, fontend, SumScore_text);
	}
	

	if (App->input->keyboard[SDL_SCANCODE_SPACE]) {

		if (App->fonts->coins > 0 && SubstractCoins == true) {

			App->fonts->coins--;
			SubstractCoins = false;
		}
		App->fade->FadeToBlack(App->gameover, App->menu, 1.0f);

	}
	
	return UPDATE_CONTINUE;
}