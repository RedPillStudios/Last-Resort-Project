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
		if (App->player->IsEnabled() == false) {
			App->player->Enable();
		}
		App->player->resetPosition();
		App->enemies->Enable();
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
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 3255, 112);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 3270, 90);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 3310, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 3300, 145);

	//}

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

	if (App->input->keyboard[SDL_SCANCODE_6] == KEY_STATE::KEY_DOWN && App->player->PlayerActivated == false) {
		App->player2->Enable();
		App->player->PlayerActivated = true;
		App->player2->Dead = false;
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
	

	// Condition to still play if pl2 is active 

		if (App->player->Dead == true && App->player2->IsEnabled()== false) {
			if (App->player->DestroyShip.Finished()) 
				App->fade->FadeToBlack(App->scene1background, App->gameover, 1.0f);
			
		}
		else if ((App->player->Dead == true && App->player2->Dead == true)) {
			if (App->player->DestroyShip.Finished()&&App->player2->DestroyShip.Finished()) {
				App->fade->FadeToBlack(App->scene1background, App->gameover, 1.0f);
			}
		}

	return UPDATE_CONTINUE;
}