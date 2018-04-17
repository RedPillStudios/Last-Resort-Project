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
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, SCREEN_WIDTH, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 400, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 470, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 540, 100);


    App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 200, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 250, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 110, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 225, 80);


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

	if (App->input->keyboard[SDL_SCANCODE_6] == KEY_STATE::KEY_DOWN && App->player2->Player2Activated == false && App->player2->lives >0) {
		App->player2->Enable();
		App->player2->Player2Activated = true;
		App->player2->Dead = false;
		App->player2->resetPosition2();
		App->player2->Ship2Collider->to_delete = false;
	}
	if (App->input->keyboard[SDL_SCANCODE_7] == KEY_STATE::KEY_DOWN && App->player->Player1Activated == false && App->player->lives >0) {
		if(App->player->IsEnabled()==false){
			App->player->Enable();
		}
		App->player->Player1Activated = true;
		App->player->Dead = false;
		App->player->resetPosition();
		App->player->Ship1Collider->to_delete = false;
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
			if (App->player->DestroyShip.Finished())                                 //EL FINISHED NO FUNCIONA EM CAGO EN LA PUTA MARE QUE EM VA PARIR
				App->fade->FadeToBlack(App->scene1background, App->gameover, 1.0f);
			
		}
		else if ((App->player->Dead == true && App->player2->Dead == true)) {
			if (App->player->DestroyShip.Finished()&&App->player2->DestroyShip.Finished()) {                     //EL FINISHED NO FUNCIONA EM CAGO EN LA PUTA MARE QUE EM VA PARIR
				App->fade->FadeToBlack(App->scene1background, App->gameover, 1.0f);
			}
		}

	
	return UPDATE_CONTINUE;
}