#include "ModuleBossLvl1.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleSceneLvl1.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "ModuleUI.h"
#include "Enemy.h"
#include "Enemy_Tears.h"

#include "SDL/include/SDL_timer.h"
#include "SDL/include/SDL.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 

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

	//position = { (9000), 55 };
	position = { (7300), 55 };
	current_head = &AnimMouth;
	current_eye = &AnimClosedEye;

	Boss = App->textures->Load("Images/Bosses/Boss_Stage1_Sprites.png");

	//Add Colliders
	Bot = App->collision->AddCollider({ position.x + 10, position.y + 95, 48, 18 }, COLLIDER_ENEMY);
	Eye = App->collision->AddCollider({ position.x + 20,position.y + 79, 25, 16 }, COLLIDER_ENEMY, this);
	Head = App->collision->AddCollider({ position.x + 8, position.y - 20, 48, 44 }, COLLIDER_ENEMY);
	Left_Arm = App->collision->AddCollider({ position.x - 14, position.y + 8, 22, 72 }, COLLIDER_ENEMY);
	Body = App->collision->AddCollider({ position.x, position.y, 95, 77}, COLLIDER_ENEMY);

	dead = false;
	life = 50;
	

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

	current_eye = nullptr;
	current_head = nullptr;

	App->textures->Unload(Boss);
	return true;
}

update_status ModuleBossLvl1::Update() {

	//srand(time(NULL));

	Bot->SetPos(position.x + 10, position.y + 95);
	Eye->SetPos(position.x + 20, position.y + 79);
	Head->SetPos(position.x + 8, position.y - 20);
	Left_Arm->SetPos(position.x - 14, position.y + 8);
	Body->SetPos(position.x, position.y);

	App->render->Blit(Boss, position.x + 10, position.y + 79 + BossTrote, &current_eye->GetCurrentFrame());
	App->render->Blit(Boss, position.x + 8, position.y - 20 + BossTrote, &current_head->GetCurrentFrame());
	App->render->Blit(Boss, position.x - 14, position.y + 8 + BossTrote, &AnimArm.GetCurrentFrame());
	App->render->Blit(Boss, position.x + 6, position.y + 48 + BossTrote, &AnimPotbelly.GetCurrentFrame());
	App->render->Blit(Boss, position.x, position.y + BossTrote, &AnimBody.GetCurrentFrame());

	//BOSS APPEAR AND MOVEMENT
	 if (position.x <= App->scene1background->position_min_limit + 200 ) {  //controla si el boss ha llagdo a su posicion
		ReachPos = true;
	 }
	 if (ReachPos ) { //controla que el boss se mueva a la derecha una  vez llagado a su posicion
		 position.x++;
	 }
	 if (ReachPos && Restartcontroller == 0) {
		 Time1 = 2000;
		 Time2 = SDL_GetTicks() + Time1;
		 Restartcontroller++;
	 }

	 if (BossTroteDelay < SDL_GetTicks() - 400) {
		 BossTrote = BossTrote * -1;
		 BossTroteDelay = SDL_GetTicks();
	 }


	 //________________________________________________________________________________________________________________________________________
	//EYE OPEN AND SHOOTS
	 
	 if (EyeBool && (cicle % 3 != 0)) {
		 Stage = Stage1;
		 if (ReachPos && Time2 < SDL_GetTicks()) { // abre el ojo 3 segundos despues de llegar
			 current_eye = &AnimOpenEye;
			 // ShootCounter = 0;
		 }

		 if (ReachPos && current_eye == &AnimOpenEye && current_eye->Finished() == true && !Shooted) { // si el ojo esta abierto, permite el shooting
			 if (Restartcontroller2 == 0) {  //controller para q dispare pasado un tiempo de 3 sec
				 Time3 = SDL_GetTicks() + (Time1 - 1700);
				 Restartcontroller2++;
			 }
			 if (SDL_GetTicks() > Time3) { // aqui se usa el controller2 para q dispare a los 3 sec
				 if (Restartcontroller3 == 0) { // otro controller, este para controlar el delay de los dos disparos
					 Time4 = SDL_GetTicks() + Time1 - 1200;
					 Restartcontroller3++;
				 }
				 if (SDL_GetTicks() > Time4 && ShootCounter == 0) {//aqui se dispara y reinicia el controler del delay de las balas
					 LOG("Shooting();");
					 Shooting();
					 Restartcontroller3 = 0;
					 ShootCounter++;
				 }
			 }
		 }
		 if (ShootCounter != 0) {
			 ShootCounter = 0;
			 Restartcontroller2 = 0;
			 Restartcontroller3 = 0;
			 EyeBool = false;
			 Stage = Stage2;
			 Time6 = SDL_GetTicks();
		 }
	 }
	 else if (!EyeBool) {
		 if (SDL_GetTicks() >= Time6 + 1500) {
			 current_eye = &AnimCloseEye;
		 }	 
	 }
	 if (!EyeBool && current_eye->Finished() == true) {
		 if (SDL_GetTicks() >= Time6 + 1500) {
			 AnimClosedEye.Reset();
			 current_eye = &AnimClosedEye;
		 }
	 }
	 //_____________________________________________________________________________________________________________________________________
	 //CHARGE ATACK HERE

	 if (current_eye == &AnimClosedEye && Stage == Stage2 && (cicle % 3 != 0)) { // si estamos en el stage2 (en el que el ataque es el de charge), necesitamos un delay para q de tiempo al boss entre el stage 1 y el 2
		 if (Restartcontroller4 == 0) {
			 Time5 = SDL_GetTicks() + (Time1);
			 Restartcontroller4++;
		}
		 if (SDL_GetTicks() > Time5) { // si ha pasado el delay del paso anterior, aqui hace la carga 1 sola vez
			 if (!EndCharge) {
				 LOG("Charge();");
				 Charge();
			 }
		 }
	 }
	// srand(time(NULL));
	 //__________________________________________________________________________________________________________________________________________
	 //LLUVIA DORADA
	 if (cicle % 3 == 0 ) {
		 Stage = Stage3;
		 AnimClosedEye.Reset();
		 AnimCloseEye.Reset();
		
		 if (Restartcontroller6 == 0) { // controler para hacer delay entre stages
			 Time7 = SDL_GetTicks() + (Time1 - 500);
			 Restartcontroller6++;
		 }
		 if (SDL_GetTicks() >= Time7 && MaleTears < 7) { // HERE goes the code for this atack
			 
			 current_eye = &AnimOpenEye;
			/* if (Restartcontroller7 == 0) {
				 Time7 = SDL_GetTicks() + Time1 - 400;
			 }*/
			 if (current_eye->Finished() == true ) {
				 if (TearShootDelay < SDL_GetTicks() - 400) { //delay
					 TearShoot = TearShoot * -1;
					 TearShootDelay = SDL_GetTicks();
				 }
				 current_head = &AnimOpenMouth;
				 if (Restartcontroller8 == 0 && PeeLimit < 8) {
					 Time8 = SDL_GetTicks()+600;
					 Restartcontroller8 = 1;
					 EnemyAddController = 0;
					 PeeLimit++;
				 }
				 if (SDL_GetTicks() >= Time8 /*TearShoot == -1*/) {
					 LluviaDorada();
					 
					 Restartcontroller8 = 0;
				
					 TearShoot == 1;
					 //EnemyAddController--;
				 } 
			 }
		 }
		 if (PeeLimit >= 7) {
			 Stage = Stage1;
			 EyeBool = true;
			 TimeCounter = true;
			 Shooted = false;
			 Forward = false;
			 Backward = false;
			 EndCharge = false;
			 Time2 = 0;
			 Time3 = 0;
			 Time4 = 0;
			 Time5 = 0;
			 Time6 = 0;
			 Restartcontroller = 0;
			 Restartcontroller2 = 0;
			 Restartcontroller3 = 0;
			 Restartcontroller4 = 0;
			 Restartcontroller5 = 0;
			 ShootCounter = 0;
			 AnimOpenEye.Reset();
			 AnimCloseEye.Reset();
			 current_head = &AnimCloseMouth;
			 cicle++;
			 PeeLimit = 0;

		 }
	 }


	 //TECLA TEST PARA REINICIAR EL OJO
	 if (App->input->keyboard[SDL_SCANCODE_K]) {
		 EyeBool = true;
	 }
	
	
	

	

	

	return UPDATE_CONTINUE;
}

void ModuleBossLvl1::OnCollision(Collider *c1, Collider *c2) {

 	//beAttacked = true; //GUYS THIS IS TO MADE THE BOSS ALLWAYS ATTACKABLE JUST FOR DEBUGGING, THIS MUST BE DELETED FOR THE GAME (could be a great debug functionality)

	if (beAttacked && (c1->type == COLLIDER_PLAYER_SHOT || c2->type == COLLIDER_PLAYER_SHOT || c1->type == COLLIDER_PLAYER_SHOT2 || c2->type == COLLIDER_PLAYER_SHOT2)) {

			--life;
			if (life <= 0) {
					App->fonts->ScoreP1 += 5000;
					App->fonts->ScoreP2 += 5000;
 					dead = true;
		}
	}
}

void ModuleBossLvl1::Shooting() {

	if (current_eye == &AnimOpenEye && current_eye->Finished() && Stage == Stage1)
	{
		App->particles->AddParticle(App->particles->BossShoot, position.x , position.y + 74, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->BossShootExplosion, position.x - 10, position.y + 59);
		//App->particles->AddParticle(App->particles->BossCoolDown, position.x - 15, position.y + 60, COLLIDER_NONE, 280);
		

		App->particles->AddParticle(App->particles->BossShoot, position.x , position.y + 74, COLLIDER_ENEMY_SHOT, 500);
		App->particles->AddParticle(App->particles->BossShootExplosion, position.x - 10, position.y + 59, COLLIDER_NONE, 500);
		//App->particles->AddParticle(App->particles->BossCoolDown, position.x - 15, position.y + 60, COLLIDER_NONE, 280);
	}
	
	
}

void ModuleBossLvl1::Charge() {

	uint speed = 6;
	if (!EndCharge && Stage == Stage2) {
		if (position.x >= App->scene1background->position_min_limit + 60 && Backward == false) {
			Forward = true;
		}
		else if (position.x <= App->scene1background->position_min_limit + 60) {
			Forward = false;
			Backward = true;
		}
		if (Forward) {
			position.x -= speed;
		}
		if (Backward) {
			position.x += 1.5;
		}
	}
	if (Backward && position.x >= App->scene1background->position_min_limit + 200){
		 EyeBool = true;
		 TimeCounter = true;
		 Shooted = false;
		 Forward = false;
		 Backward = false;
		EndCharge = false;
		 Time2 = 0;
		 Time3 = 0;
		 Time4 = 0;
		 Time5 = 0;
		 Time6 = 0;
		 Restartcontroller = 0;
		Restartcontroller2 = 0;
		Restartcontroller3 = 0;
		 Restartcontroller4 = 0;
		 Restartcontroller5 = 0;
		 ShootCounter = 0;
		 AnimOpenEye.Reset();
		 AnimCloseEye.Reset();
		 cicle++;
	}
	
}
void ModuleBossLvl1::LluviaDorada() {
	
	randnum = rand() % 1;
	if (Stage == Stage3) {
		if (EnemyAddController == 0) {
			App->enemies->AddEnemy(ENEMY_TYPES::BOSS_TEARS, position.x+randnum, position.y, false);
			EnemyAddController++;
		
		}
		
	}
}


