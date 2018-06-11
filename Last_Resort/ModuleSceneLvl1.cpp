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
#include "Iron_Craw.h"
#include "ModuleUI.h"
#include "ModuleTank.h"

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

	//lights background
	Bluelight.PushBack({ 69,0,4,87 });
	Bluelight.PushBack({ 73,0,21,87 });
	Bluelight.PushBack({ 100,0,25,79 });
	Bluelight.PushBack({ 73,0,21,87 });

	Bluelight.speed = 0.03f;


	YellowLight.PushBack({ 132,0,25,143 });//
	YellowLight.PushBack({ 157,0,38,143 });//
	YellowLight.PushBack({ 157,0,38,143 });//----white
	YellowLight.PushBack({ 195,0,52,143 });//
	YellowLight.PushBack({ 247,0,65,143 });//
	YellowLight.PushBack({ 312,0,81,143 });//
	YellowLight.PushBack({ 393,0,99,143 });// 
	YellowLight.PushBack({ 0,145,121,289 });//
	YellowLight.PushBack({ 121,145,142,289 });//
	//marcha atras
	YellowLight.PushBack({ 121,145,142,289 });//
	YellowLight.PushBack({ 0,145,121,289 });//
	YellowLight.PushBack({ 393,0,99,143 });// 
	YellowLight.PushBack({ 312,0,81,143 });//
	YellowLight.PushBack({ 247,0,65,143 });//
	YellowLight.PushBack({ 195,0,52,143 });//
	YellowLight.PushBack({ 157,0,38,143 });//
	YellowLight.PushBack({ 132,0,25,143 });//
	YellowLight.loop = true;
	YellowLight.speed = 0.03f;

	Streetlight.PushBack({ 0,0,53,69 });
	Streetlight.PushBack({ 53,0,53,69 });
	Streetlight.PushBack({ 106,0,53,69 });
	Streetlight.PushBack({ 159,0,53,69 });
	Streetlight.PushBack({ 0,69,53,69 });
	Streetlight.speed = 0.008f;


	Streetlight2.PushBack({ 0,69,53,69 });
	Streetlight2.PushBack({ 0,0,53,69 });
	Streetlight2.PushBack({ 53,0,53,69 });
	Streetlight2.PushBack({ 106,0,53,69 });
	Streetlight2.PushBack({ 159,0,53,69 });

	Streetlight2.speed = 0.008f;

	minispaceships.PushBack({ 0 ,0,9,4 });
	minispaceships.PushBack({ 11,0,9,4 });
	minispaceships.PushBack({ 22,0,9,4 });
	minispaceships.PushBack({ 33,0,9,4 });
	minispaceships.PushBack({ 44,0,9,3 });
	minispaceships.PushBack({ 55,0,9,4 });
	minispaceships.PushBack({ 66,0,9,4 });
	minispaceships.PushBack({ 77,0,9,4 });
	minispaceships.speed = 0.01;
	minispaceships.loop = true;

	//srand(2);


}

ModuleSceneLvl1::~ModuleSceneLvl1()
{}

// Load assets
bool ModuleSceneLvl1::Start()
{
	LOG("Loading background assets");

	App->fonts->counterRanking = 0;

	//if (App->fonts->Checkpoint1 == false) {

		position_max_limit = SCREEN_WIDTH;
		position_min_limit = 0;
		App->render->camera.x = 0;
		posCars = 0;
	//}
	/*else if (App->fonts->Checkpoint1 == true) {

		App->render->camera.x = 9510;
		App->scene1background->position_max_limit = 3500;
		App->scene1background->position_min_limit = 3170;
	}*/

	//order of position in the game
	graphics_Crater_Boss_Zone = App->textures->Load("Images/Background_Lvl1/Boss_Static_Background.png");
	graphics_ThirdPlaneBackground = App->textures->Load("Images/Background_Lvl1/ThirdPlaneBackground.png");
	graphics_SecondPlaneBackground = App->textures->Load("Images/Background_Lvl1/SecondPlaneBackground.png");
	graphics_FirstPlaneBackGround = App->textures->Load("Images/Background_Lvl1/FirstPlaneBackGround.png");
	graphics = App->textures->Load("Images/Player/Ship&Ball_Sprite.png"); // arcade version
	Laser_Sprites = App->textures->Load("Images/Background_Lvl1/Lasers_Sprite.png");
	graphics_Streetlight = App->textures->Load("Images/Background_Lvl1/Farols_Animations.png");
	Minispaceship_texture = App->textures->Load("Images/Particles/BossWeapons&parts_EnemyShip&structure_Multiple-effects-and-explosions_Sprites.png");
	//Music
	Stage1 = App->sound->LoadMusic("Audio/Stage1/Jack_to_the_Metro_Stage1.ogg");
	Stage1_Boss_Music = App->sound->LoadMusic("Audio/Stage1/Stage1_Boss_Music.ogg");

	Mix_PlayMusic(Stage1, -1);
	//Mix_VolumeMusic(MIX_MAX_VOLUME/3);

	App->fonts->P1Life = 3;
	App->fonts->P2Life = 3;
	App->fonts->ScoreP1 = 0;
	App->fonts->ScoreP2 = 0;

	if (IsEnabled()) {
		App->enemies->Enable();
		App->powerup->Enable();
		App->Boss->Enable();
		App->collision->Enable();
		App->particles->Enable();
		App->BossTank->Enable();

	}
	if (App->player->IsEnabled() == false && App->fonts->P1Life > 0) {
		App->player->Enable();
		App->player->resetPosition();
	}
	/*if (App->player2->IsEnabled() == false && App->fonts->P2Life > 0) {
		App->player2->Enable();
		App->player2->resetPosition2();
	}
*/

	//Enemies
	//WASP->Wave1{
	//troop1
 //Wasps
	App->powerup->AddPowerUp(POWERUP_TYPES::SPEED, 300, 75);
	App->powerup->AddPowerUp(POWERUP_TYPES::SPEED, 500, 75);
	App->powerup->AddPowerUp(POWERUP_TYPES::SPEED, 600, 75);
	//App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_BEE, 700, 20, false);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 500, 60);
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

	/*App->powerup->AddPowerUp(POWERUP_TYPES::MISILES, 200, 150);
	App->powerup->AddPowerUp(POWERUP_TYPES::BOMB, 250, 150);*/

  //Bees
	/*App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_BEE, 300, 60, false);*/
	/* App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_BEE, 300, 60, false);*/
	// App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_BEE, 300, 60, false);
	/*App->enemies->AddEnemy(ENEMY_TYPES::BOSSLAMELLA, 300, 60, false);*/


	//App->powerup->AddPowerUp(POWERUP_TYPES::LASER, 790, 20);

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
  
	/*App->powerup->AddPowerUp(POWERUP_TYPES::MISILES, 1075, 65);
	App->powerup->AddPowerUp(POWERUP_TYPES::BOMB, 1025, 65);*/

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
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 1315, 145); //
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 1355, 145);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 1395, 145);



	//Rhino->Wave1
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 2425, 75);
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
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 2920, 75);//





//	App->powerup->AddPowerUp(POWERUP_TYPES::LASER, 1315, 145);
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
	//if(App->fonts->Checkpoint1 == false){
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 3200, 112);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 3240, 145);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 3265, 112);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 3280, 90);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 3320, 75);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 3310, 145);
		//App->powerup->AddPowerUp(POWERUP_TYPES::MISILES, 3310, 145);
//	}

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



	//LAST TROOPP
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 8000, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 8040, 130);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 8080, 155);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 8120, 170);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 8160, 180);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 9000, 160);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 9040, 160);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 9080, 140);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 9120, 50);

	

	//Wave2
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 5890, 77);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 5945, 77);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 5985, 77);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 6025, 77);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 6065, 77);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 6105, 77);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 6145, 77);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 6515, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 6555, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 6595, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_RHINO, 6635, 60);

	
	//HRETANNK


	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_BEE, 6840, 40, false);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_BEE, 7300, 20, false);
	

	//ZICZAC
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_ZICZAC,3560, 50, true);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_ZICZAC, 8000, 60, true);
		
	App->enemies->AddEnemy(ENEMY_TYPES::BOSSLAMELLA, 11000, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::BOSSLAMELLA, 12000, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::BOSSLAMELLA, 13000, 60);

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
	App->textures->Unload(Laser_Sprites);
	App->textures->Unload(graphics_Streetlight);
	App->textures->Unload(Minispaceship_texture);

	App->sound->UnloadMusic(Stage1);
	App->sound->UnloadMusic(Stage1_Boss_Music);

	App->player->Disable();
	App->player2->Disable();
	App->powerup->Disable();
	App->collision->Disable();
	App->particles->Disable();
	App->enemies->Disable();
	App->BossTank->Disable();
	App->MiniBoss->Disable();
	App->Boss->Disable();
	//App->Boss->BossMoves = false;

	return true;
}
// Update: draw background
update_status ModuleSceneLvl1::Update() {

    position_max_limit++;
	position_min_limit++;

	//Add player to the game
	if (App->player->IsEnabled() == false && App->fonts->P1Life > 0 && App->player->Dead == true) {
		App->player->Enable();
		App->player->resetPosition();
	}
	if (App->player2->IsEnabled() == false && App->fonts->P2Life > 0 && App->player2->Dead == true) {
		App->player2->Enable();
		App->player2->resetPosition2();
	}

	//fades
	//direct win
	if (App->input->keyboard[SDL_SCANCODE_F2])
		App->fade->FadeToBlack(App->scene1background, App->stageclear, 3.0f);
	//direct lose
	if (App->input->keyboard[SDL_SCANCODE_F3])
		App->fade->FadeToBlack(App->scene1background, App->gameover, 3.0f);

	//camera Mov
	App->render->camera.x += SCREEN_SIZE;

	//LAMELLA SPAWNERS
	if (position_min_limit == 3950)
	{
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 33, 26);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 33, 74);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 33, 123);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 33, 171);

		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 260, 26);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 260, 74);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 260, 123);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 260, 171);

	}

	if (position_min_limit == 4400)
	{
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 40, 97);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 56, 52);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 104, 32);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 152, 24);

		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 202, 32);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 250, 52);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 266, 97);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 250, 142);

		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 200, 162);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 152, 170 );
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 104, 162);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 56, 142);

	}

	if (position_min_limit == 4850)
	{
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 39, 25);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 87, 33);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 136, 57);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 200, 82);

		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 249, 65);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 265, 25);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 265, 170);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 216, 162);

		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 168, 138);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 103, 114);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 55, 130);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 39, 170);

	}

	if (position_min_limit == 5300)
	{
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 33, 26);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 33, 74);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 33, 123);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 33, 171);

		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 260, 26);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 260, 74);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 260, 123);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_LAMELLA, position_min_limit + 260, 171);

	}
	
	//background
	App->render->Blit(graphics_Crater_Boss_Zone, 0, 0, &CraterBossZone, 0.0f);

	

	App->render->Blit(graphics_ThirdPlaneBackground, 0, 0, NULL, 0.1f);

	App->render->Blit(Minispaceship_texture, 0 + xxx, yyy + 5, &minispaceships.GetCurrentFrame(), 0.3f);
	App->render->Blit(Minispaceship_texture, -20 + xxx, yyy + 10, &minispaceships.GetCurrentFrame(), 0.3f);
	App->render->Blit(Minispaceship_texture, 0 + xxx, yyy + 15, &minispaceships.GetCurrentFrame(), 0.3f);

	App->render->Blit(Minispaceship_texture, -280 + xxx, yyy + 20, &minispaceships.GetCurrentFrame(), 0.3f);
	App->render->Blit(Minispaceship_texture, -300 + xxx, yyy + 20, &minispaceships.GetCurrentFrame(), 0.3f);
	App->render->Blit(Minispaceship_texture, -320 + xxx, yyy + 20, &minispaceships.GetCurrentFrame(), 0.3f);


	App->render->Blit(Minispaceship_texture, -630 + xxx, yyy + 30, &minispaceships.GetCurrentFrame(), 0.3f);
	App->render->Blit(Minispaceship_texture, -650 + xxx, yyy + 35, &minispaceships.GetCurrentFrame(), 0.3f);
	App->render->Blit(Minispaceship_texture, -670 + xxx, yyy + 30, &minispaceships.GetCurrentFrame(), 0.3f);

	App->render->Blit(Minispaceship_texture, -1190 + xxx, yyy + 25, &minispaceships.GetCurrentFrame(), 0.3f);
	App->render->Blit(Minispaceship_texture, -1210 + xxx, yyy + 25, &minispaceships.GetCurrentFrame(), 0.3f);
	App->render->Blit(Minispaceship_texture, - 1170+ xxx, yyy + 25, &minispaceships.GetCurrentFrame(), 0.3f);

	App->render->Blit(Minispaceship_texture, -1630 + xxx, yyy + 40, &minispaceships.GetCurrentFrame(), 0.3f);
	App->render->Blit(Minispaceship_texture, -1650 + xxx, yyy + 45, &minispaceships.GetCurrentFrame(), 0.3f);
	App->render->Blit(Minispaceship_texture, -1640 + xxx, yyy + 40, &minispaceships.GetCurrentFrame(), 0.3f);

	//lights
	App->render->Blit(Laser_Sprites, 400, 0, &YellowLight.GetCurrentFrame(), 0.3f);
	App->render->Blit(Laser_Sprites, 196, -17, &Bluelight.GetCurrentFrame(), 0.3f);
	App->render->Blit(Laser_Sprites, 710, -17, &Bluelight.GetCurrentFrame(), 0.3f);
	App->render->Blit(Laser_Sprites, 800, 0, &YellowLight.GetCurrentFrame(), 0.3f);
	App->render->Blit(Laser_Sprites, 855, -15, &Bluelight.GetCurrentFrame(), 0.3f);
	App->render->Blit(Laser_Sprites, 1200, 0, &YellowLight.GetCurrentFrame(), 0.3f);
	App->render->Blit(Laser_Sprites, 1600, 0, &YellowLight.GetCurrentFrame(), 0.3f);
	//minidetails
	xxx++;
	yyy = 60;
	
	
	//background
	App->render->Blit(graphics_SecondPlaneBackground, 0, 30, NULL, 0.3f);
	App->render->Blit(graphics_FirstPlaneBackGround, 0, 0, NULL, 0.5f); // FIRST PLANE BACKGROUND
	StreetlightCreator();
	//CARS

	if (position_max_limit<= 7160) {
		randomPositionCars = rand() % 2 + 1;

		if ((posCars % 100 == 0) || posCars % 90 == 0) {
			if (randomPositionCars == 1) {
				App->enemies->AddEnemy(ENEMY_TYPES::CARS, posCars, 195);
			}
			else if (randomPositionCars == 2) {
				App->enemies->AddEnemy(ENEMY_TYPES::CARS, posCars, 210);
			}
		}
		posCars++;
	}

	
	//BOSS Music
	if (position_max_limit == 8900) {
		
		timeFadeInt = SDL_GetTicks();
		
		Mix_FadeOutMusic(3000);

		switchMusic = true;
	}
	
	if (position_max_limit > 8900 && timeFadeInt < SDL_GetTicks() - 3300 && switchMusic == true) {
			
		Mix_FadeInMusic(Stage1_Boss_Music, -1, 3000);

		switchMusic = false;
	}
	//PLAYER 2 APPEAR
	if (App->input->keyboard[SDL_SCANCODE_P]) {
		if (App->player2->IsEnabled() == false && App->fonts->P2Life > 0) {
		App->player2->Enable();
		App->player2->resetPosition2();
		}
	}

	// FADE IF NO MORE LIVES
	if (App->player2->IsEnabled() == false && App->fonts->P1Life <= 0) {
		App->fade->FadeToBlack(App->scene1background, App->gameover, 1.0f);
		Mix_FadeOutMusic(3000);
	}
	else if (App->player2->IsEnabled() == true && App->fonts->P1Life <= 0 && App->fonts->P2Life <= 0) {
		App->fade->FadeToBlack(App->scene1background, App->gameover, 1.0f);
		Mix_FadeOutMusic(3000);
	}
	

	//Boss Spawn

	if (App->player->position.x >= 9000-(SCREEN_WIDTH-20) || App->player2->positionp2.x >= 9000- (SCREEN_WIDTH - 20)) {
		App->Boss->Enable();
	

		if (App->Boss->position.x > App->scene1background->position_min_limit && App->Boss->position.x < App->scene1background->position_max_limit-100)
			App->Boss->BossMoves = true;
	}
	//Tank boos disable
	if (App->player->IsEnabled() == false && App->player2->IsEnabled() == false) {
		App->BossTank->DestroyTank == true;
	}
	if (App->BossTank->DestroyTank == true && App->BossTank->IsEnabled() == true) {
		App->BossTank->Disable();
		LOG(" Tank disabled");
	}


	//Iron Spawn

	if (position_max_limit >= 1300&& IronCraw1==false) {
		IronCraw1 = true;
		App->MiniBoss->Enable();
	}
	if (position_max_limit > 7400 && IronCraw1 == true && IronCraw2 == false) {
		IronCraw2 = true;
		App->MiniBoss->Enable();
	}

	// iron craw disable

	if (App->player->IsEnabled() == false && App->player2->IsEnabled() == false) {
		App->MiniBoss->disablingIronCraw == true;
	}
	if (App->MiniBoss->disablingIronCraw == true && App->MiniBoss->IsEnabled()) {
		App->MiniBoss->Disable();
		LOG(" Iron disabled");
	}

	if (App->MiniBoss->position.x < App->scene1background->position_min_limit && App->MiniBoss->disablingIronCraw == false)
		App->MiniBoss->Disable();
  
  
	//FINAL BOSS DISABLE NeedToDisableBoss = true;
	if (App->Boss->NeedToDisableBoss == true && counterfordisable == false) {
		App->Boss->Disable();
		counterfordisable = true;
		App->Boss->dead = true;
	}

	////second Iron Spawn
	//if (App->scene1background->position_max_limit >= 7700) {
	//	IronCraw2 = true;
	//	App->MiniBoss->Enable();

	//Fade if boss is dead
	if(App->Boss->dead){

  		//App->player->TopScore += 10000;
		App->Boss->Disable();
		App->fade->FadeToBlack(App->scene1background, App->stageclear, 1.0f);
		
	}

	//Checkpoints
	/*if (position_max_limit == 3500 && App->fonts->coins > 0)
		App->fonts->Checkpoint1 = true;*/

	return UPDATE_CONTINUE;
}

void ModuleSceneLvl1::StreetlightCreator() { //DIOOOOOOS ROGER ENSERIO "MODUL"?
	int pos = 39;
	int modul = 0;
	for (int i = 0; i < 27; i++) {
		if (modul % 2 == 0)
			App->render->Blit(graphics_Streetlight, pos, 133, &Streetlight.GetCurrentFrame(), 0.5f);
		else if (modul % 1 == 0)
			App->render->Blit(graphics_Streetlight, pos, 133, &Streetlight2.GetCurrentFrame(), 0.5f);

		pos += 64;
		modul++;

	}
}
