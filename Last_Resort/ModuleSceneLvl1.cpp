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
#include "ModuleMainMenu.h"
#include "ModuleMainMenu.h"
#include "ModuleGameOver.h"
#include "ModuleStageClear.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModulePowerUp.h"
#include "ModuleBossLvl1.h"

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

	position_max_limit = SCREEN_WIDTH;
	position_min_limit = 0;

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

	P1Coins = 3;
	P2Coins = 3;

	if (IsEnabled()) {
		App->enemies->Enable();
		App->powerup->Enable();
		App->Boss->Enable();
	}
	if (App->player->IsEnabled() == false && App->scene1background->P1Coins > 0) {
		App->player->Enable();
		App->player->resetPosition();
	}
	if (App->player2->IsEnabled() == false && App->scene1background->P2Coins >0) {
		App->player2->Enable();
		App->player2->resetPosition2();
	}

	//Enemies
	//WASP->Wave1{
	//troop1
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 500, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 540, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 580, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 580, 145);

	//troop2
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 630, 20);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 650, 145);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 670, 20);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 710, 20);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 750, 20);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 790, 20);

	//troop3
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 795, 145);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 835, 145);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 875, 145);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 915, 145);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 955, 145);

	//troop4
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 970, 110);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 995, 135);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 995, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 1035, 115);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 1035, 85);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 1095, 95);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 1075, 65);

	//troop5
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 1155, 20);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 1195, 20);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 1235, 20);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 1275, 20);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 1315, 20);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 1155, 145);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 1195, 145);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 1235, 145);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 1275, 145);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 1315, 145);
	// }

	//WASP->Wave2{
	//troop1
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 1900, 30);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 1940, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 1980, 90);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 2020, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 2060, 150);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 2100, 150);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 2140, 150);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 2180, 150);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 2220, 150);
	//}

	//WASP->Wave3{
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP,3200, 112);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 3240, 145);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 3265, 112);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 3280, 90);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 3320, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 3310, 145);
	//}

	//WASP->wave4
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 3700, 145);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 3740, 115);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 3780, 85);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 3820, 55);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 3860, 55);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 3900, 55);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 3940, 55);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 3980, 55);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 4020, 55);

	//Rhino->Wave1
	/*App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 525, 75);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 570, 75);*/
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 2425,75);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 2470, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 2515, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 2560, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 2605, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 2650, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 2695, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 2740, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 2785, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 2830, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 2875, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 2920, 75);

	//Wave2
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 5500, 77);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 5540, 77);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 5580, 77);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 5620, 77);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 5660, 77);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 5700, 77);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 5740, 77);
  
	 //wave3
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 5860, 60);//these are not well located!!!!!!!!!!!!!!!!!!!!!!!!
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 6960, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 7060, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 7160, 60);

	//ZICZAC
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_ZICZAC,3560, 145);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_ZICZAC, 7560, 60);

	//CARS
	App->enemies->AddEnemy(ENEMY_TYPES::CARS,-10, 195);

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
	App->textures->Unload(graphics);

	App->player->Disable();
	App->player2->Disable();
	App->powerup->Disable();
	App->Boss->Disable();
	App->collision->Disable();
	App->particles->Disable();
	App->enemies->Disable();
	return true;
}
// Update: draw background
update_status ModuleSceneLvl1::Update() {

    position_max_limit++;
	position_min_limit++;

	//Add player to the game
	if (App->player->IsEnabled() == false && P1Coins > 0 && App->player->Dead == true) {
		App->player->Enable();
		App->player->resetPosition();
	}
	if (App->player2->IsEnabled() == false && P2Coins > 0 && App->player2->Dead == true) {
		App->player2->Enable();
		App->player2->resetPosition2();
	}

	//camera Mov
	App->render->camera.x += 1*SCREEN_SIZE;
	
	App->render->Blit(graphics_ThirdPlaneBackground, 0, 0, NULL, 0.1f);
	App->render->Blit(graphics_SecondPlaneBackground, 0, 30, NULL, 0.3f);
	App->render->Blit(graphics_FirstPlaneBackGround, 0, 0, NULL,0.5f); // FIRST PLANE BACKGROUND

	if (App->input->keyboard[SDL_SCANCODE_F2])
		App->fade->FadeToBlack(App->scene1background, App->stageclear, 3.0f);
	if (App->input->keyboard[SDL_SCANCODE_F3])
		App->fade->FadeToBlack(App->scene1background, App->gameover, 3.0f);

	App->render->Blit(graphics_Crater_Boss_Zone, 0, 0, &CraterBossZone, 0.0f);
	App->render->Blit(graphics_ThirdPlaneBackground, 0, 0, NULL, 0.1f);
	App->render->Blit(graphics_SecondPlaneBackground, 0, 30, NULL, 0.3f);
	App->render->Blit(graphics_FirstPlaneBackGround, 0, 0, NULL, 0.5f); // FIRST PLANE BACKGROUND

	// FADE IF NOT ENOUGHT COINS
	if (P1Coins <= 0 && P2Coins <= 0 && App->player->Dead == true && App->player2->Dead == true) {

		App->fade->FadeToBlack(App->scene1background, App->gameover, 1.0f); 
	}

	//Fade if boss is dead
	if(App->Boss->dead == true){

		App->fade->FadeToBlack(App->scene1background, App->stageclear, 1.0f);
	}

	return UPDATE_CONTINUE;
}