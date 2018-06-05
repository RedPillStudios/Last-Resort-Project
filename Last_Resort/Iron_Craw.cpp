
#include "Iron_Craw.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleSceneLvl1.h"
#include "ModuleInput.h"
#include "ModuleUI.h"
#include "Moduleplayer.h"
#include "Enemy.h"


#include "SDL/include/SDL_timer.h"
#include "SDL/include/SDL.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>




Iron_Craw::Iron_Craw()
{
	//idle body
	FirstIdle.PushBack({269,190,42,59});
	idle.PushBack({139,123,42,59});

	//idle body damage
	idle_Damage.PushBack({181,123,42,59});

	//Left_arm

	Left_Arm.PushBack({ 1,0,46,62});
	Left_Arm.PushBack({ 46,2,46,60 });
	Left_Arm.PushBack({ 92,0,46,62 });
	Left_Arm.PushBack({ 138,0,46,62 });
	Left_Arm.PushBack({ 184,0,46,62 });

	Left_Arm.PushBack({ 1,64,46,60 });
	Left_Arm.PushBack({ 46,61,46,62 });
	Left_Arm.PushBack({ 92,61,46,60 });
	Left_Arm.PushBack({ 138,61,46,60 });
	Left_Arm.PushBack({ 184,61,46,59 });

	Left_Arm.PushBack({ 1,124,46,61 });
	Left_Arm.PushBack({ 46,124,46,61 });
	Left_Arm.PushBack({ 92,124,46,61 });

	Left_Arm.loop = true;
	Left_Arm.speed = 0.1f;
	 
	//right_arm

	Right_Arm.PushBack({ 261,0, 46, 62 });
	Right_Arm.PushBack({ 307,2, 46, 60 });
	Right_Arm.PushBack({ 353,0, 46, 62 });
	Right_Arm.PushBack({ 399,0, 46, 62 });
	Right_Arm.PushBack({ 445,0, 46, 62 });

	Right_Arm.PushBack({ 261,64,46,60 });
	Right_Arm.PushBack({ 307,62,46,62 });
	Right_Arm.PushBack({ 352,63,46,60 });
	Right_Arm.PushBack({ 399,62,46,60 });
	Right_Arm.PushBack({ 445,63,46,59 });

	Right_Arm.PushBack({ 261,124,46,61 });	
	Right_Arm.PushBack({ 307,124,46,61 });
	Right_Arm.PushBack({353,124,46,61 });

	Right_Arm.loop = true;
	Right_Arm.speed = 0.1f;

	//legs
	leg1.PushBack({223,158,18,24});
	leg2.PushBack({242,158,18,24 });

	//blue circle

	blueCircle.PushBack({ 1,214,30,30 });
	blueCircle.PushBack({31,214,30,30});
	blueCircle.PushBack({61,214,30,30});
	blueCircle.PushBack({91,214,30,30});
	blueCircle.loop = true;
	blueCircle.speed = 0.12f;

	
}


Iron_Craw::~Iron_Craw()
{
}


bool Iron_Craw::Start() {

	if (App->scene1background->IronCraw2 == false)
		SpawnPos = 1200;
	else
		SpawnPos = 8000;

	position = {(SpawnPos),-10.0};

  
	Mini_Boss= App->textures->Load("Images/Bosses/First_Mini_Boss_Sprite.png");
	Damaged = App->textures->Load("Images/Bosses/First_Mini_Boss_Damage_Sprite.png");

	body = App->collision->AddCollider({(int)position.x, (int)position.y , 42, 59 }, COLLIDER_ENEMY,this);
	LArm= App->collision->AddCollider({ (int)position.x-40,(int)position.y , 39, 62 }, COLLIDER_ENEMY,this);
	RArm = App->collision->AddCollider({ (int)position.x +38, (int)position.y , 39, 62 }, COLLIDER_ENEMY,this);

	Current_AnimationBody =&FirstIdle;
	actual = Mini_Boss;
	PlayerPosition = App->player->position;

	LArmPosition = position.y;
	RArmPosition = position.y;

	dead = false;
	life =50;
	

	armsOut = true;
	armsOut2 = true;
	moving_Down = true;
	EnemyAppear = true;
	ExplosionDead = true;
	LArmfallinf = false;
	Rarmfalling = false;
	launchBombs =false;
	spawnMovementDown = false;


	return true;
}

update_status Iron_Craw::Update() {
	if (EnemyAppear) {
		spawn();
		
	}

	if (hit == true) {
		counter_Flicker++;
		if (counter_Flicker % 3 == 0) {
			actual = Damaged;
		}
		else {
			actual = Mini_Boss;
		}
		if (counter_Flicker >= 30) {
			actual = Mini_Boss;
			counter_Flicker = 0;
			hit = false;
		}
	}

	if (!dead) {
		body->SetPos(position.x, position.y);

		if (armsOut) {
			RArm->SetPos(position.x + 38, position.y);
		}
		else {
			RArm->changeCollider(COLLIDER_TYPE::COLLIDER_NONE);

		}
		if (SpawnFInished) {


			if (!dead) {
				body->SetPos(position.x, position.y);

				if (armsOut) {
					RArm->SetPos(position.x + 38, position.y);
				}
				else {
					RArm->changeCollider(COLLIDER_TYPE::COLLIDER_NONE);

				}


				if (armsOut2) {
					LArm->SetPos(position.x - 40, position.y);
				}
				else {

					LArm->changeCollider(COLLIDER_TYPE::COLLIDER_NONE);

				}
				position.x++;


				//App->render->Blit(Mini_Boss, position.x - 9, position.y + 18, &blueCircle.GetCurrentFrame());
				//App->render->Blit(Mini_Boss, position.x + 20, position.y + 18, &blueCircle.GetCurrentFrame());
				//App->render->Blit(Mini_Boss, position.x - 3, position.y + 37, &leg1.GetCurrentFrame());
				//App->render->Blit(Mini_Boss, position.x + 27, position.y + 37, &leg2.GetCurrentFrame());
				//App->render->Blit(Mini_Boss, position.x, position.y, &Current_AnimationBody->GetCurrentFrame());
				//App->render->Blit(Mini_Boss, position.x + 38, RArmPosition, &Right_Arm.GetCurrentFrame());
				//App->render->Blit(Mini_Boss, position.x - 44,LArmPosition, &Left_Arm.GetCurrentFrame());

			}


			if (life < 40 && life>30)
				Current_AnimationBody = &idle;

			if (life < 30)
				Current_AnimationBody = &idle_Damage;

			if (life <= 15 && life > 10) {

				Rarmfalling = true;
				if (armsOut) {
					App->particles->AddParticle(App->particles->EnemyExplosion, position.x + 35, position.y);
					App->particles->AddParticle(App->particles->EnemyExplosion, position.x - 35, position.y + 10);
					App->particles->AddParticle(App->particles->FogExplosion, position.x + 35, position.y + 20);
					App->particles->AddParticle(App->particles->EnemyExplosion, position.x, position.y + 15);

					App->particles->AddParticle(App->particles->FogExplosion, position.x + 35, RArmPosition);
					App->particles->AddParticle(App->particles->FogExplosion, position.x - 35, LArmPosition - 20);
					App->particles->AddParticle(App->particles->FogExplosion, position.x + 35, RArmPosition + 10);


					armsOut = false;
				}


			}

			if (life < 7)
				position.x--;

			if (counterGreenBomb >= 500 && counterGreenBomb <= 510) {
				launchBombs = true;
				counterGreenBomb = 0;
			}


			if (!dead) {

				Move();
				if (launchBombs) {
					bombs();
					launchBombs = false;
				}
			}



			if (Rarmfalling) {
				RArmPosition++;

			}


			if (life <= 5 && life > 0) {

				LArmfallinf = true;
				if (armsOut2) {
					App->particles->AddParticle(App->particles->EnemyExplosion, position.x - 40, position.y);
					App->particles->AddParticle(App->particles->EnemyExplosion, position.x + 40, position.y - 10);
					App->particles->AddParticle(App->particles->EnemyExplosion, position.x + 40, position.y + 10);

					App->particles->AddParticle(App->particles->FogExplosion, position.x - 40, position.y - 10);

					App->particles->AddParticle(App->particles->FogExplosion, position.x - 40, LArmPosition);
					App->particles->AddParticle(App->particles->FogExplosion, position.x - 40, LArmPosition - 20);
					App->particles->AddParticle(App->particles->FogExplosion, position.x - 40, LArmPosition + 10);
				}


				armsOut2 = false;
			}


			if (LArmfallinf) {
				LArmPosition++;


			}

			if (life <= 0) {

				dead = true;
				position.x++;

				body->changeCollider(COLLIDER_TYPE::COLLIDER_NONE);
				position.x++;
				position.y++;

				if (dyingParticles) {

					App->particles->AddParticle(App->particles->FogExplosion, position.x + 30, position.y + 10);
					App->particles->AddParticle(App->particles->FogExplosion, position.x - 30, position.y + 10);
					App->particles->AddParticle(App->particles->FogExplosion, position.x, position.y);


					dyingParticles = false;

				}

			}
			counterGreenBomb++;

			if (dead &&  ExplosionDead && position.y >= 200) {



				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x + 50, (int)position.y);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x, (int)position.y + -2);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x + -14, (int)position.y);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x, (int)position.y + 33);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x + 22, (int)position.y);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x, (int)position.y + 5);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x + 44, (int)position.y + -2);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x + 43, (int)position.y + 33);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x, (int)position.y + 15);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x + 1, (int)position.y - 10);

				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x + 33 + 4, (int)position.y + 22 + 5);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x + 21 - 10, (int)position.y - 28 - 15);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x + 55 - 15, (int)position.y - 3);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x, (int)position.y - 44 + 20);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x + 66 + 7, (int)position.y);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x, (int)position.y + 5 + 5);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x + 40 - 5, (int)position.y + 44 - 12);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x + 35 - 12, (int)position.y - 23 + 3);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x + 30, (int)position.y + 40 - 8);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x + 70 + 12, (int)position.y - 30 + 12);

				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x + 90, (int)position.y + 12);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x + 69, (int)position.y - 58);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x + 97, (int)position.y - 2);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x + 80, (int)position.y - 54);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x + 120, (int)position.y);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x, (int)position.y + 12);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x + 110, (int)position.y + 24);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x + 98, (int)position.y - 33);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x, (int)position.y + 30);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)position.x + 81, (int)position.y - 44);

				ExplosionDead = false;
				disablingIronCraw = true;
			}

		

		}

	
	}
	
	App->render->Blit(Mini_Boss, position.x - 9, position.y + 18, &blueCircle.GetCurrentFrame());
	App->render->Blit(Mini_Boss, position.x + 20, position.y + 18, &blueCircle.GetCurrentFrame());
	App->render->Blit(Mini_Boss, position.x - 3, position.y + 33, &leg1.GetCurrentFrame());
	App->render->Blit(Mini_Boss, position.x + 27, position.y + 33, &leg2.GetCurrentFrame());
	App->render->Blit(Mini_Boss, position.x, position.y, &Current_AnimationBody->GetCurrentFrame());
	App->render->Blit(Mini_Boss, position.x + 38, RArmPosition, &Right_Arm.GetCurrentFrame());
	App->render->Blit(Mini_Boss, position.x - 44, LArmPosition, &Left_Arm.GetCurrentFrame());

	return UPDATE_CONTINUE;
}


bool Iron_Craw::CleanUp() {

	if (body != nullptr) {
		body->to_delete = true;
		body = nullptr;
	}

	if (LArm != nullptr) {
		LArm->to_delete = true;
		LArm = nullptr;
	}

	if (RArm != nullptr) {
		RArm->to_delete = true;
		RArm = nullptr;
	}

	App->textures->Unload(Mini_Boss);
	App->textures->Unload(Damaged);

	Current_AnimationBody = nullptr;
	
	//if(!disablingIronCraw)
	//	disablingIronCraw = true;

	return true;
}


void Iron_Craw::spawn() {

	position.x++;

	body->SetPos(position.x, position.y);
	RArm->SetPos(position.x + 38, position.y);
	LArm->SetPos(position.x - 40, position.y);

	//if (spawnMovementDown == false ) {
	//	position.y -= 0.5f;
	//	RArmPosition -= 0.5f;
	//	LArmPosition -= 0.5f;
	//}
	if (position.y <=30) {
		spawnMovementDown = true;

	}

	if (spawnMovementDown == true) {
        position.y += 0.2f;
		RArmPosition += 0.2f;
		LArmPosition += 0.2;
		
		if (position.y <=55) {
			spawnMovementDown = false;
			SpawnFInished = true;
			EnemyAppear = false;
			
		}
	}
}


void Iron_Craw::Move() {
	

	if (moving_Down == true) {
		if (position.y < MIN_HEIGHT_MINIBOSS) {
			position.y++;
			if (!Rarmfalling)
				RArmPosition++;
			if(!LArmfallinf)
				LArmPosition++;
			
		}
		if (position.y >= MIN_HEIGHT_MINIBOSS) {
			counterIron++;
			if (counterIron >= 250) {
				moving_Up = true;
				moving_Down = false;
				counterIron = 0;
			}

		}
	}
	if (moving_Up == true) {
		if (position.y > MAX_HEIGHT_MINIBOSS) {
			position.y--;
			if (!Rarmfalling)
			RArmPosition--;
			if (!LArmfallinf)
			LArmPosition--;
		}
		if (position.y<=MAX_HEIGHT_MINIBOSS) {
			counterIron++;
			if (counterIron >=250) {
				moving_Up = false;
				moving_Down = true;
				counterIron = 0;
			}
		}
	}
}

void Iron_Craw::bombs() {
	
	App->enemies->AddEnemy(ENEMY_TYPES::GREENBOMB, position.x+20, position.y+20,COLLIDER_TYPE::COLLIDER_ENEMY_SHOT);
	App->enemies->AddEnemy(ENEMY_TYPES::GREENBOMB, position.x - 20, position.y + 20, COLLIDER_TYPE::COLLIDER_ENEMY_SHOT);
	App->enemies->AddEnemy(ENEMY_TYPES::GREENBOMB, position.x + 20, position.y , COLLIDER_TYPE::COLLIDER_ENEMY_SHOT);
	App->enemies->AddEnemy(ENEMY_TYPES::GREENBOMB, position.x - 20, position.y , COLLIDER_TYPE::COLLIDER_ENEMY_SHOT);

}

void Iron_Craw::OnCollision(Collider *c1, Collider *c2) {

	if ((c1->type == COLLIDER_PLAYER_SHOT || c2->type == COLLIDER_PLAYER_SHOT || c1->type == COLLIDER_PLAYER_SHOT2 || c2->type == COLLIDER_PLAYER_SHOT2)) {

		--life;
		hit = true;
		if (life <= 0) {
			App->fonts->ScoreP1 +=1000;
			App->fonts->ScoreP2 += 1000;
			dead = true;
		}

	}




}