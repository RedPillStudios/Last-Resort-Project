//#include "Application.h"
//#include "ModuleTextures.h"
//#include "ModuleInput.h"
//#include "Animation.h"
//#include "Globals.h"
//#include "ModuleParticles.h"
//#include "ModuleRender.h"
//#include "ModulePlayer.h"
//#include "ModuleSound.h"
//#include "ModuleTextures.h"
//
//#include "ModuleEnemies.h"
//
//#define MAX_WASPS 20
//
//ModuleEnemies::ModuleEnemies() {
//
//	_Wasp.PushBack({ 0,178,32,16 });
//	_Wasp.PushBack({ 0,194,32,15 });
//	_Wasp.PushBack({ 0,225,32,16 });
//	_Wasp.PushBack({ 0,240,32,15 });
//	_Wasp.PushBack({ 0,256,32,16 });
//	_Wasp.speed = 0.1f;
//}
//
//
//ModuleEnemies::~ModuleEnemies()
//{
//}
//
//bool ModuleEnemies::Start() {
//
//	LOG("Starting Module Enemies");
//	graphics = App->textures->Load("Images/General/Common_enemies_Sprite.png");
//	return true;
//}
//
//bool ModuleEnemies::CleanUp() {
//
//	LOG("Cleaning Up Enemies Module");
//	App->textures->Unload(graphics);
//	return true;
//}
//
//update_status ModuleEnemies::Update() {
//
//	int a = 20;
//	Wasp = _Wasp.GetCurrentFrame();
//
//	while (a <= MAX_WASPS) {
//
//		App->render->Blit(graphics, SCREEN_WIDTH + 35, SCREEN_HEIGHT - 50, &Wasp, 0.0f);
//		App->render->Blit(graphics, SCREEN_WIDTH + 35, SCREEN_HEIGHT - 300, &Wasp, 0.0f);
//
//		
//	}
//	
//}