#include "ModuleBossLvl1.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleSceneLvl1.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"


#include "SDL/include/SDL_timer.h"
#include <stdlib.h>

ModuleBossLvl1::ModuleBossLvl1() {

	//Eye
	AnimOpenEye.PushBack({ 340, 34, 45, 34 });
	AnimOpenEye.PushBack({ 385, 34, 45, 34 });
	AnimOpenEye.PushBack({ 430, 34, 45, 34 });
	AnimOpenEye.PushBack({ 295, 0, 45, 34 });
	AnimOpenEye.loop = false;
	AnimOpenEye.speed = 0.1f;

	AnimCloseEye.PushBack({ 430, 34, 45, 34 });
	AnimCloseEye.PushBack({ 385, 34, 45, 34 });
	AnimCloseEye.PushBack({ 340, 34, 45, 34 });
	AnimCloseEye.PushBack({ 295, 34, 45, 34 });
	AnimCloseEye.loop = false;
	AnimCloseEye.speed = 0.1f;
	
	AnimClosedEye.PushBack({ 295, 34, 45, 34 });

	//Mouth
	AnimOpenMouth.PushBack({ 0,133,48,44 });
	AnimOpenMouth.PushBack({ 48,133,48,44 });
	AnimOpenMouth.PushBack({ 96,133,48,44 });
	AnimOpenMouth.PushBack({ 144,133,48,44 });
	AnimOpenMouth.PushBack({ 192,133,48,44 });
	AnimOpenMouth.loop = false;
	AnimOpenMouth.speed = 0.1f;

	AnimCloseMouth.PushBack({ 192,133,48,44 });
	AnimCloseMouth.PushBack({ 144,133,48,44 });
	AnimCloseMouth.PushBack({ 96,133,48,44 });
	AnimCloseMouth.PushBack({ 48,133,48,44 });
	AnimCloseMouth.PushBack({ 0,133,48,44 });
	AnimCloseMouth.loop = false;
	AnimCloseMouth.speed = 0.1f;

	AnimMouth.PushBack({ 0,133,48,44 });

	//Body
	AnimBody.PushBack({ 96, 177, 95, 77 });
	AnimBody.PushBack({ 191, 177, 95, 77 });
	AnimBody.PushBack({ 286, 177, 95, 77 });
	AnimBody.PushBack({ 381, 177, 95, 77 });
	AnimCloseMouth.loop = false;
	AnimBody.speed = 0.1f;

	//Left Arm
	AnimArm.PushBack({ 0,177, 22, 72 });
	AnimArm.PushBack({ 22,177, 22, 72 });
	AnimArm.PushBack({ 44,177, 22, 72 });
	AnimArm.PushBack({ 66,177, 22, 72 });
	AnimArm.loop = true;
	AnimArm.speed = 0.1f;

	//Potbelly (Barriga in Spanish)
	AnimPotbelly.PushBack({ 240, 145, 42,32 });
	AnimPotbelly.PushBack({ 282, 145, 42,32 });
	AnimPotbelly.PushBack({ 324, 145, 42,32 });
	AnimPotbelly.loop = true;
	AnimPotbelly.speed = 0.2f;

}

ModuleBossLvl1::~ModuleBossLvl1() {}

bool ModuleBossLvl1::Start() {

	position = { (9000), 55 };
	
	current_head = &AnimMouth;
	current_eye = &AnimClosedEye;

	Boss = App->textures->Load("Images/Bosses/Boss_Stage1_Sprites.png");

	//Add Colliders
	Bot = App->collision->AddCollider({ position.x + 10, position.y + 95, 48, 18 }, COLLIDER_ENEMY);
	Eye = App->collision->AddCollider({ position.x + 20,position.y + 79, 25, 16 }, COLLIDER_ENEMY, this);
	Head = App->collision->AddCollider({ position.x + 8, position.y - 20, 48, 44 }, COLLIDER_ENEMY);
	Left_Arm = App->collision->AddCollider({ position.x - 14, position.y + 8, 22, 72 }, COLLIDER_ENEMY);
	Body = App->collision->AddCollider({ position.x, position.y, 95, 77}, COLLIDER_ENEMY);

	dead == false;
	life = 10;

	return true;
}

bool ModuleBossLvl1::CleanUp() {

	LOG("Cleaning Up Boss Lvl1");
	if (Bot != nullptr)
		Bot->to_delete = true;
	if (Eye != nullptr)
		Eye->to_delete = true;
	if (Head != nullptr)
		Head->to_delete = true;
	if (Left_Arm != nullptr)
		Left_Arm->to_delete = true;
	if (Body != nullptr)
		Body->to_delete = true;

	App->textures->Unload(Boss);
	return true;
}

update_status ModuleBossLvl1::Update() {

	Bot->SetPos(position.x + 10, position.y + 95);
	Eye->SetPos(position.x + 20, position.y + 79);
	Head->SetPos(position.x + 8, position.y - 20);
	Left_Arm->SetPos(position.x - 14, position.y + 8);
	Body->SetPos(position.x, position.y);

	if (BossMoves){
		position.x++;
}
	App->render->Blit(Boss, position.x + 10, position.y + 79, &current_eye->GetCurrentFrame());
	App->render->Blit(Boss, position.x + 8, position.y - 20, &current_head->GetCurrentFrame());
	App->render->Blit(Boss, position.x - 14, position.y + 8, &AnimArm.GetCurrentFrame());
	App->render->Blit(Boss, position.x + 6, position.y + 48, &AnimPotbelly.GetCurrentFrame());
	App->render->Blit(Boss, position.x, position.y, &AnimBody.GetCurrentFrame());

	Attack();

	return UPDATE_CONTINUE;
}

void ModuleBossLvl1::OnCollision(Collider *c1, Collider *c2) {

	beAttacked = true; //GUYS THIS IS TO MADE THE BOSS ALLWAYS ATTACKABLE JUST FOR DEBUGGING, THIS MUST BE DELETED FOR THE GAME (could be a great debug functionality)

	if (beAttacked && (c1->type == COLLIDER_PLAYER_SHOT || c2->type == COLLIDER_PLAYER_SHOT || c1->type == COLLIDER_PLAYER_SHOT2 || c2->type == COLLIDER_PLAYER_SHOT2)) {

			--life;
			if (life <= 0) {
					App->player->ScoreP1 += 5000;
					App->player2->ScoreP2 += 5000;
					dead = true;
					App->Boss->Disable();
					Eye->rect = { 0, 0 };
					Head->rect = { 0, 0 }; //Comment this please
		}
		
	}
}

void ModuleBossLvl1::Shooting() {

	App->particles->AddParticle(App->particles->BossShoot, position.x + 20, position.y + 74, COLLIDER_ENEMY_SHOT);
	App->particles->AddParticle(App->particles->BossCoolDown, position.x - 20, position.y + 73, COLLIDER_NONE, 280);
	App->particles->AddParticle (App->particles->BossShootExplosion, position.x - 10, position.y + 59);
	App->particles->AddParticle(App->particles->BossShoot, position.x + 20, position.y + 74, COLLIDER_ENEMY_SHOT, 2000);
	App->particles->AddParticle(App->particles->BossCoolDown, position.x - 20, position.y + 73, COLLIDER_NONE, 2280);
	App->particles->AddParticle(App->particles->BossShootExplosion, position.x - 10, position.y + 59);
}

void ModuleBossLvl1::Charge() {

	uint Speed = 5;

	if (current_eye == &AnimOpenEye && current_eye->Finished()) {

		AnimOpenEye.Reset();
		current_eye = &AnimCloseEye;
	}
	if (current_eye->Finished()) {

		if (position.x <= (30 + App->scene1background->position_min_limit) && Left) {

			Left = false;
			Right = false;
		}

		if (Left)
			position.x += Speed;

		if (Right && position.x <= (220 + App->scene1background->position_min_limit))
			position.x++;

		if (Right && position.x >= (220 + App->scene1background->position_min_limit)) {

			Left = true;
			Right = false;
			ChargeAttack = false;
			current_eye = &AnimOpenEye;
			AnimCloseEye.Reset();
		}
	}
}

void ModuleBossLvl1::Attack() {

	if(Wait1){

		Shooting();
		Wait1 = false;
		Wait2 = true;
	}
	/*if (Wait2) {

		Charge();
		Wait2 = false;
		Wait1 = true;
	}
	*/
	if (current_eye == &AnimOpenEye && current_eye->Finished())
		beAttacked = true;
	else
		beAttacked = false;

	/*if (ChargeAttack)
		Charge();*/
}