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
	//Ball measures
	Ball.x = 140;
	Ball.y = 178;
	Ball.w = 26;
	Ball.h = 26;
}

ModuleSceneLvl1::~ModuleSceneLvl1()
{}

// Load assets
bool ModuleSceneLvl1::Start()
{
	LOG("Loading background assets");


	//order of position in the game
	graphics_Crater_Boss_Zone = App->textures->Load("Images/Background_Lvl1/Boss_Static_Background.png");
	graphics_ThirdPlaneBackground = App->textures->Load("Images/Background_Lvl1/ThirdPlaneBackground.png");
	graphics_SecondPlaneBackground = App->textures->Load("Images/Background_Lvl1/SecondPlaneBackground.png");
	graphics_FirstPlaneBackGround = App->textures->Load("Images/Background_Lvl1/FirstPlaneBackGround.png");
	graphics = App->textures->Load("Images/Player/Ship&Ball_Sprite.png"); // arcade version

	BallCollider = App->collision->AddCollider({ 140, 178, 26, 26 }, COLLIDER_ENEMY, this);

	//Music
	Stage1 = App->sound->LoadMusic("Audio/Stage1/Jack_to_the_Metro_Stage1.ogg");
	Mix_PlayMusic(Stage1, -1);
	Mix_Volume(-1, VOLUME_MUSIC);

	if (IsEnabled()) {
		if (App->player->IsEnabled() == false) {
			App->player->Enable();
		}
		App->player->resetPosition();
	}
	//if (IsEnabled() == false) {
	//	if (App->player->IsEnabled() == true) {
	//		App->player->Disable();
	//	}
	//}
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
	FirstPlaneBackGround_position_X = 0;
	SecondPlaneGround_position_X = 0;
	ThirdPlaneBackground_position_X = 0;

	return true;
}
// Update: draw background
update_status ModuleSceneLvl1::Update()
{
	//LOOKING TO MAKE PLAYER 2 APPEAR INDEPENDENT FROM PLAYER 1

	//Appear/Disappear player 2
	if (App->input->keyboard[SDL_SCANCODE_6] == KEY_STATE::KEY_DOWN && App->player->pressed == false) {
		App->player->pressed = true;
		App->player2->Dead = false;
		App->player2->Enable();
		App->player2->resetPosition2();

	
	}

	//else if (App->input->keyboard[SDL_SCANCODE_6] == KEY_STATE::KEY_DOWN && App->player->pressed == true) {
	//	App->player2->Ship2Collider->to_delete = true;
	//	App->player->pressed = false;
	//	App->player2->Disable();
	//}


	float Speed_Foreground=3;
	float Speed_Background=1;
	float Speed_Midground=2;
	
	FirstPlaneBackGround_position_X -= Speed_Foreground;
	SecondPlaneGround_position_X -= Speed_Midground;
	ThirdPlaneBackground_position_X -= Speed_Background;
	BallCollider->SetPos(100, SCREEN_HEIGHT / 2);

	// Draw everything --------------------------------------
	App->render->Blit(graphics_Boss_Static_Background, 0, 0, &CraterBossZone, 0.0f); // CRATER ZONE FIRST BOSS
	App->render->Blit(graphics_ThirdPlaneBackground, (int)(ThirdPlaneBackground_position_X/3.3), 0, &ThirdPlaneBackground, 1.0f); // THIRD PLANE
	App->render->Blit(graphics_SecondPlaneBackground, (int)(SecondPlaneGround_position_X/3), 30, &SecondPlaneBackground, 1.0f); //SECOND PLANE BACKGROUND
	App->render->Blit(graphics_FirstPlaneBackGround, (int)(FirstPlaneBackGround_position_X/2), 0, &FirstPlaneBackGround, 1.0f); // FIRST PLANE BACKGROUND
	App->render->Blit(graphics, 100, SCREEN_HEIGHT / 2, &Ball, 0.0f);


	if (App->input->keyboard[SDL_SCANCODE_1]) {
		App->fade->FadeToBlack(App->scene1background, App->gameover, 3.0f);
	}

	if (App->input->keyboard[SDL_SCANCODE_2]) {
		App->fade->FadeToBlack(App->scene1background, App->stageclear, 3.0f);
	}

	// Condition to still play if pl2 is active 

		if (App->player->Dead == true && App->player2->IsEnabled()== false) {
			if (App->player->DestroyShip.Finished()) {
				App->fade->FadeToBlack(App->scene1background, App->gameover, 1.0f);
			}
		}
		else if ((App->player->Dead == true && App->player2->Dead == true)) {
			if (App->player->DestroyShip.Finished()&&App->player2->DestroyShip.Finished()) {
				App->fade->FadeToBlack(App->scene1background, App->gameover, 1.0f);
			}
		}



	return UPDATE_CONTINUE;
}