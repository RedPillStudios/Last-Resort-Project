#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"
#include "ModuleSound.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleBackground::ModuleBackground()
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



	
}

ModuleBackground::~ModuleBackground()
{
}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	//order of position in the game
	

	graphics_Boss_Static_Background = App->textures->Load("Images/Background_Lvl1/Boss_Static_Background.png");
	graphics_ThirdPlaneBackground = App->textures->Load("Images/Background_Lvl1/ThirdPlaneBackground.png");
	graphics_SecondPlaneBackground = App->textures->Load("Images/Background_Lvl1/SecondPlaneBackground.png");
	graphics_FirstPlaneBackGround = App->textures->Load("Images/Background_Lvl1/FirstPlaneBackGround.png");

	Stage1=App->sound->LoadMusic("Game/Audio/Stage1/Jack_to_Metro_Stage1.ogg");

	Mix_PlayMusic(Stage1,-1);
	
	Mix_Volume(-1, MIX_MAX_VOLUME / 2);
	


	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{

	float Speed_Foreground=3;
	float Speed_Background=1;
	float Speed_Midground=2;

	//background movements!!! HERE---> The images are the ones which move, not the camera.
	if (FirstPlaneBackGround_position_X < 4077) {
		FirstPlaneBackGround_position_X -= Speed_Foreground;
	}
	if (SecondPlaneGround_position_X < 972) {
		SecondPlaneGround_position_X -= Speed_Midground;
	}
	if (ThirdPlaneBackground_position_X < 472) {
		ThirdPlaneBackground_position_X -= Speed_Background;
	}
	
	

	// Draw everything --------------------------------------



	App->render->Blit(graphics_ThirdPlaneBackground, (ThirdPlaneBackground_position_X)/3.5, 0, &ThirdPlaneBackground, 1.0f);
	App->render->Blit(graphics_SecondPlaneBackground, (SecondPlaneGround_position_X)/3, 30, &SecondPlaneBackground, 1.0f); //SECOND PLANE BACKGROUND
	App->render->Blit(graphics_FirstPlaneBackGround, (FirstPlaneBackGround_position_X)/2, 0, &FirstPlaneBackGround, 1.0f); // FIRST PLANE BACKGROUND
	
	




	return UPDATE_CONTINUE;
}