#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "ModuleSceneLvl1.h"
#include "ModuleSound.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneLvl2.h"
#include "ModuleMainMenu.h"
#include "ModuleMainMenu.h"
#include "ModuleGameOver.h"
#include "ModuleStageClear.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneLvl1::ModuleSceneLvl1()
{
	// background1 
	FirstPlaneBackGround.x = 0;
	FirstPlaneBackGround.y = 0;
	FirstPlaneBackGround.w = 4407; //works
	FirstPlaneBackGround.h = 238; //also works
	//background2
	SecondPlaneBackground.x = 0;
	SecondPlaneBackground.y = 0;
	SecondPlaneBackground.w = 1302;
	SecondPlaneBackground.h = 159;
	//background3
	ThirdPlaneBackground.x = 0;
	ThirdPlaneBackground.y = 0;
	ThirdPlaneBackground.w = 802;
	ThirdPlaneBackground.h = 159;
	//CraterBossZone
	CraterBossZone.x = 0;
	CraterBossZone.y = 0;
	CraterBossZone.w = SCREEN_WIDTH;
	CraterBossZone.h = SCREEN_HEIGHT;

	

}

ModuleSceneLvl1::~ModuleSceneLvl1()
{}

// Load assets
bool ModuleSceneLvl1::Start()
{
	LOG("Loading background assets");

	App->render->camera.x = 0;
	//order of position in the game
	graphics_Crater_Boss_Zone = App->textures->Load("Images/Background_Lvl1/Boss_Static_Background.png");
	graphics_ThirdPlaneBackground = App->textures->Load("Images/Background_Lvl1/ThirdPlaneBackground.png");
	graphics_SecondPlaneBackground = App->textures->Load("Images/Background_Lvl1/SecondPlaneBackground.png");
	graphics_FirstPlaneBackGround = App->textures->Load("Images/Background_Lvl1/FirstPlaneBackGround.png");
	graphics = App->textures->Load("Images/Player/Ship&Ball_Sprite.png"); // arcade version
 
	//Music
	Stage1 = App->sound->LoadMusic("Audio/Stage1/Jack_to_the_Metro_Stage1.ogg");
	Mix_PlayMusic(Stage1, -1);
	Mix_Volume(-1, VOLUME_MUSIC);

	if (IsEnabled()) {
		App->enemies->Enable();
	}
	if (App->player->IsEnabled() == false && App->scene1background->coins >0) {
		App->player->Enable();
		App->player->resetPosition();
	}
	if (App->player2->IsEnabled() == false && App->scene1background->coins >0) {
		App->player2->Enable();
		App->player2->resetPosition2();
	}
	//Enemies
	/*App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, SCREEN_WIDTH, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 400, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 470, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 540, 100);*/


    App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 200, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 250, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 110, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 225, 80);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 200, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 250, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 110, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 225, 100);


	if (App->collision->IsEnabled()==false) {
		App->collision->Enable();
	}
	return true;
}

//Unload Assets

bool ModuleSceneLvl1::CleanUp() {

	LOG("Unloaded Lvl 1 Scene  ERROR: ", SDL_GetError());

	App->textures->Unload(graphics_ThirdPlaneBackground);
	App->textures->Unload(graphics_FirstPlaneBackGround);
	App->textures->Unload(graphics_SecondPlaneBackground);
	App->textures->Unload(graphics_Crater_Boss_Zone);

	App->collision->Disable();
	App->enemies->Disable();
	return true;
}
// Update: draw background
update_status ModuleSceneLvl1::Update() {

    position_max_limit++;
	position_min_limit++;

	

	//Add player to the game
	if (App->player->IsEnabled() == false && coins > 0 && App->player->Dead == true) {
		App->player->Enable();
		App->player->resetPosition();
	}
	if (App->player2->IsEnabled() == false && coins > 0 && App->player2->Dead == true) {
		App->player2->Enable();
		App->player2->resetPosition2();
	}


		

	//camera Mov
	App->render->camera.x += 1*SCREEN_SIZE;
	
	App->render->Blit(graphics_ThirdPlaneBackground, 0, 0, NULL, 0.1f);
	App->render->Blit(graphics_SecondPlaneBackground, 0, 30, NULL, 0.3f);
	App->render->Blit(graphics_FirstPlaneBackGround, 0, 0, NULL,0.5f); // FIRST PLANE BACKGROUND

	if (App->input->keyboard[SDL_SCANCODE_1]) 
		App->fade->FadeToBlack(App->scene1background, App->gameover, 3.0f);
	
	if (App->input->keyboard[SDL_SCANCODE_2]) 
		App->fade->FadeToBlack(App->scene1background, App->stageclear, 3.0f);
	

	

	// FADE IF NOT ENOUGHT COINS
	
	if (coins <= 0 && (App->player->Dead == true && App->player2->Dead == true)) {
		App->player->Disable();
		App->player2->Disable();
		App->fade->FadeToBlack(App->scene1background, App->gameover, 1.0f); 
	}




	


	return UPDATE_CONTINUE;
}


