
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


#include "SDL/include/SDL_timer.h"
#include "SDL/include/SDL.h"
#include <stdlib.h>
#include <stdio.h>




Iron_Craw::Iron_Craw()
{
	//idle body
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

	position = {(1050), 55 };

	Mini_Boss= App->textures->Load("Images/Bosses/First_Mini_Boss_Sprite.png");


	body = App->collision->AddCollider({ position.x, position.y , 42, 59 }, COLLIDER_ENEMY,this);
	LArm= App->collision->AddCollider({ position.x-40, position.y , 39, 62 }, COLLIDER_ENEMY,this);
	RArm = App->collision->AddCollider({ position.x +38, position.y , 39, 62 }, COLLIDER_ENEMY,this);

	Current_AnimationBody =&idle;

	PlayerPosition = App->player->position;

	LArmPosition = position.y;
	RArmPosition = position.y;

	dead = false;
	life =50;

	return true;
}

update_status Iron_Craw::Update() {
	if (!dead) {
		body->SetPos(position.x, position.y);
		LArm->SetPos(position.x - 40, position.y);
		RArm->SetPos(position.x + 38, position.y);

		position.x++;
		

		App->render->Blit(Mini_Boss, position.x - 9, position.y + 18, &blueCircle.GetCurrentFrame());
		App->render->Blit(Mini_Boss, position.x + 20, position.y + 18, &blueCircle.GetCurrentFrame());
		App->render->Blit(Mini_Boss, position.x - 3, position.y + 37, &leg1.GetCurrentFrame());
		App->render->Blit(Mini_Boss, position.x + 27, position.y + 37, &leg2.GetCurrentFrame());
		App->render->Blit(Mini_Boss, position.x, position.y, &Current_AnimationBody->GetCurrentFrame());
		App->render->Blit(Mini_Boss, position.x + 38, RArmPosition, &Right_Arm.GetCurrentFrame());
		App->render->Blit(Mini_Boss, position.x - 44,LArmPosition, &Left_Arm.GetCurrentFrame());

	}




	

	if (life < 30)
		Current_AnimationBody = &idle_Damage;

	if (life == 10) {
		armsOut = true;
		Rarmfalling = true;
		if (armsOut) {
			App->particles->AddParticle(App->particles->EnemyExplosion, position.x + 35, position.y);
			App->particles->AddParticle(App->particles->EnemyExplosion, position.x + 35, position.y+10);
			App->particles->AddParticle(App->particles->FogExplosion, position.x + 35, position.y + 10);
			/*App->particles->AddParticle(App->particles->FogExplosion, position.x + 35, position.y -10);*/

			armsOut = false;
		}
		App->particles->AddParticle(App->particles->FogExplosion, position.x + 35, RArmPosition);
		App->particles->AddParticle(App->particles->FogExplosion, position.x + 35, RArmPosition+10);


	
		
		

	}
	
	if (Rarmfalling) {
		position.x += 0.001*(PlayerPosition.x - position.x);
		position.y += 0.001*(PlayerPosition.y - position.y);

		RArmPosition++;
		
	}


	if (life == 5) {
		armsOut2 = true;
		LArmfallinf = true;
		if (armsOut2) {
			App->particles->AddParticle(App->particles->EnemyExplosion, position.x - 40, position.y);
			App->particles->AddParticle(App->particles->EnemyExplosion, position.x - 40, position.y - 10);
			App->particles->AddParticle(App->particles->FogExplosion, position.x - 40, position.y - 10);
		/*	App->particles->AddParticle(App->particles->FogExplosion, position.x - 40, position.y + 10);*/

			armsOut2 = false;
		}
		App->particles->AddParticle(App->particles->FogExplosion, position.x - 40, LArmPosition);
		App->particles->AddParticle(App->particles->FogExplosion, position.x - 40, LArmPosition+10);
	}


	if (LArmfallinf) {
		LArmPosition++;
		
	}

	if (life==0) {
		dead = true;
		Disable();
	}

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


	moveIron_Craw = true;

	if ( moveIron_Craw == true && moving_Down==false) {
	
		position.y--;
		
		if (position.y == MAX_HEIGHT_MINIBOSS) {
			position.y = position.y;
			moving_Down = true;
		}

	}

	
	else if (moving_Down == true && moveIron_Craw == true) {
			position.y++;

		if (position.y == MIN_HEIGHT_MINIBOSS) {
			position.y = position.y;
			moving_Down = false;
			moveIron_Craw = false;
		}

	}



}

void Iron_Craw::bombs() {
	


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