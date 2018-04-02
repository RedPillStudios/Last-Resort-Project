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
	
	graphics_Boss_Static_Background = App->textures->Load("Boss_Static_Background.png");
	graphics_ThirdPlaneBackground = App->textures->Load("ThirdPlaneBackground.png");
	graphics_SecondPlaneBackground = App->textures->Load("SecondPlaneBackground.png");
	graphics_FirstPlaneBackGround = App->textures->Load("FirstPlaneBackGround.png");

	/*Stage1 = Mix_LoadMUS("Jack to the Metro [STAGE 1]");*/


	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	//background movements!!! HERE---> The images are the ones which move, not the camera.
	if (FirstPlaneBackGround_position_X < 4077) {
		FirstPlaneBackGround_position_X -=0.5;
	}
	if (SecondPlaneGround_position_X < 972) {
		SecondPlaneGround_position_X = FirstPlaneBackGround_position_X / 2;
	}
	if (ThirdPlaneBackground_position_X < 472) {
		ThirdPlaneBackground_position_X = FirstPlaneBackGround_position_X / 3;
	}
	

	// Draw everything --------------------------------------
	App->render->Blit(graphics_ThirdPlaneBackground, ThirdPlaneBackground_position_X, 0, &ThirdPlaneBackground, 1.0f);
	App->render->Blit(graphics_SecondPlaneBackground, SecondPlaneGround_position_X, 30, &SecondPlaneBackground, 1.0f); //SECOND PLANE BACKGROUND
	App->render->Blit(graphics_FirstPlaneBackGround, FirstPlaneBackGround_position_X, 0, &FirstPlaneBackGround, 1.0f); // FIRST PLANE BACKGROUND
	

	return UPDATE_CONTINUE;
}