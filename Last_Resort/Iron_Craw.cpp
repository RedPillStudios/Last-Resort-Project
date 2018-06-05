
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

	position = {(150),55 };

	Mini_Boss= App->textures->Load("Images/Bosses/First_Mini_Boss_Sprite.png");


	body = App->collision->AddCollider({ position.x, position.y , 42, 59 }, COLLIDER_ENEMY,this);
	LArm= App->collision->AddCollider({ position.x-40, position.y , 39, 62 }, COLLIDER_ENEMY,this);
	RArm = App->collision->AddCollider({ position.x +38, position.y , 39, 62 }, COLLIDER_ENEMY,this);

	Current_AnimationBody =&FirstIdle;

	PlayerPosition = App->player->position;

	LArmPosition = position.y;
	RArmPosition = position.y;

	dead = false;
	life =50;

	armsOut = true;
	armsOut2 = true;
	moving_Down = true;
	LArmfallinf = false;
	Rarmfalling = false;
	launchBombs = true;

	return true;
}

update_status Iron_Craw::Update() {

	if (!dead ) {
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

	if (life <= 10 && life>5) {
		position.x--;

		Rarmfalling = true;
		if (armsOut) {
			App->particles->AddParticle(App->particles->EnemyExplosion, position.x + 35, position.y);
			App->particles->AddParticle(App->particles->EnemyExplosion, position.x - 35, position.y+10);
			App->particles->AddParticle(App->particles->FogExplosion, position.x + 35, position.y + 10);
			
			App->particles->AddParticle(App->particles->FogExplosion, position.x + 35, RArmPosition);
			App->particles->AddParticle(App->particles->FogExplosion, position.x + 35, RArmPosition + 10);


			armsOut = false;
		}
		
	
	}
	
	if (!dead) {
		
		Move();
	/*	if (launchBombs) {
			bombs();
			launchBombs = false;
		}*/
	}


	if (Rarmfalling) {
		RArmPosition++;
		
	}


	if (life <= 5 && life>0) {
		position.x--;
		LArmfallinf = true;
		if (armsOut2) {
			App->particles->AddParticle(App->particles->EnemyExplosion, position.x - 40, position.y);
			App->particles->AddParticle(App->particles->EnemyExplosion, position.x + 40, position.y - 10);
			App->particles->AddParticle(App->particles->FogExplosion, position.x - 40, position.y - 10);
		
			App->particles->AddParticle(App->particles->FogExplosion, position.x - 40, LArmPosition);
			App->particles->AddParticle(App->particles->FogExplosion, position.x - 40, LArmPosition + 10);
		}


			armsOut2 = false;
		}
		

	if (LArmfallinf) {
		LArmPosition++;
	
		
	}

	if (life<=0) {
	
		dead = true;

		body->changeCollider(COLLIDER_TYPE::COLLIDER_NONE);
		position.x++;
		position.y++;
		
		if (dyingParticles) {
			
			App->particles->AddParticle(App->particles->FogExplosion, position.x+30,position.y+10);
			App->particles->AddParticle(App->particles->FogExplosion, position.x - 30, position.y + 10);
			App->particles->AddParticle(App->particles->FogExplosion, position.x , position.y);
			

			dyingParticles = false;

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

	Current_AnimationBody = nullptr;

	return true;
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
			if (counterIron >= 300) {
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
			if (counterIron >= 300) {
				moving_Up = false;
				moving_Down = true;
				counterIron = 0;
			}
		
		}


	}

	

}

void Iron_Craw::bombs() {
	
	
	/*App->enemies->AddEnemy(ENEMY_TYPES::HUMAN, position.x, position.y, false);*/

	/*counterGreenBomb++;
	PlayerPosition = App->player->position;
	if (counterGreenBomb>=70) {

	
	
		
		App->particles->AddParticle(App->particles->GreenBomb, position.x + 20, position.y-20, COLLIDER_TYPE::COLLIDER_ENEMY_SHOT);

	


		counterGreenBomb = 0;
	}
	
	angleBomb = radians * (180 / PI);
	radians = atan2((PlayerPosition.y - position.y), (PlayerPosition.x - position.x));


	App->particles->GreenBomb.Speed.x = 3 * (cos(angleBomb*PI / 180));
	App->particles->GreenBomb.Speed.x++;
	App->particles->GreenBomb.Speed.y = 3 * (sin(angleBomb*PI / 180));*/


	


}
	

	











void Iron_Craw::OnCollision(Collider *c1, Collider *c2) {

	if ((c1->type == COLLIDER_PLAYER_SHOT || c2->type == COLLIDER_PLAYER_SHOT || c1->type == COLLIDER_PLAYER_SHOT2 || c2->type == COLLIDER_PLAYER_SHOT2)) {

		--life;
		if (life <= 0) {
			App->fonts->ScoreP1 +=1000;
			App->fonts->ScoreP2 += 1000;
			dead = true;
		}

	}


}