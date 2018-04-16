#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleGameOver.h"
#include "ModuleSound.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMainMenu.h"
#include "ModuleSceneLvl1.h"
#include "ModuleSceneLvl2.h"
#include "ModuleStageClear.h"

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

}


ModuleGameOver::~ModuleGameOver()
{
}

bool ModuleGameOver::Start() {

		LOG("Loading Game Over Screen");
		graphics_GameOverImage = App->textures->Load("Images/Congrats/GameOver.png");
		GameOver = App->sound->LoadMusic("Audio/Congrats/GameOver.ogg");
  
		Mix_Volume(-1,VOLUME_MUSIC);
		Mix_PlayMusic(GameOver, 0);

		/*if (IsEnabled()) {
			if (App->player->IsEnabled()) {
				App->player->Disable();
			}
		}*/
	
	return true;
}

bool ModuleGameOver::CleanUp() {

	LOG("Unloading Game Over Screen");
	App->textures->Unload(graphics_GameOverImage);

	return true;
}

update_status ModuleGameOver::Update() {

	App->render->Blit(graphics_GameOverImage, 0, 0, &Background, 0);

	if (App->input->keyboard[SDL_SCANCODE_SPACE]) {
		App->fade->FadeToBlack(App->gameover, App->menu,1.0f);
	}
	
	return UPDATE_CONTINUE;
}