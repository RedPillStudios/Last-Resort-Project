//#include "Globals.h"
//#include"Application.h"
//#include "ModuleTextures.h"
//#include "ModuleRender.h"
//#include "ModulePlayer.h"
//#include "ModuleInput.h"
//#include "ModuleSound.h"
//#include "ModuleFadeToBlack.h"
//
//#include "ModuleSceneLvl1.h"
//#include "ModuleSceneLvl2.h"
//#include "ModuleStageClear.h"
//#include "ModuleMainMenu.h"
//#include "ModuleGameOver.h"
//
//
//
//ModuleStageClear::ModuleStageClear() {}
//
//
//ModuleStageClear::~ModuleStageClear()
//{
//}
//
//bool ModuleStageClear::Start() {
//
//	LOG("Starting Module Stage Clear");
//
//	graphics_StageClearLabel = App->textures->Load("Images/Congrats/UI_MainGame_Sprite.png");
//
//	StageClearMusic = App->sound->LoadMusic("Audio/Stage_Clear/Stage_Clear.ogg");
//	Mix_Volume(-1, MIX_MAX_VOLUME / 9);
//	Mix_PlayMusic(StageClearMusic, 0);
//
//	if (IsEnabled()) {
//
//		if (App->player->IsEnabled()) {
//
//			App->player->Disable();
//		}
//	}
//	return true;
//}
//
//bool ModuleStageClear::CleanUp() {
//
//	LOG("Unloading Textures in Stage Clear Screen");
//	App->textures->Unload(graphics_StageClearLabel);
//
//	return true;
//}
//
//update_status ModuleStageClear::Update() {
//
//	//App->particles->AddParticle(App->stageclear->Label1, ((SCREEN_WIDTH / 2) - 106.5f), ((SCREEN_HEIGHT / 2) - 8));
//	
//
//	if (App->input->keyboard[SDL_SCANCODE_1]) {
//		App->fade->FadeToBlack(App->stageclear, App->menu, 3.0f);
//	}
//	if (App->input->keyboard[SDL_SCANCODE_2]) {
//		App->fade->FadeToBlack(App->stageclear, App->scene1background, 3.0f);
//	}
//	if (App->input->keyboard[SDL_SCANCODE_3]) {
//		App->fade->FadeToBlack(App->stageclear, App->scene2background, 3.0f);
//	}
//	if (App->input->keyboard[SDL_SCANCODE_4]) {
//		App->fade->FadeToBlack(App->stageclear, App->gameover, 3.0f);
//	}
//
//	return UPDATE_CONTINUE;
//}