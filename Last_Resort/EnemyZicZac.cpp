
#include "Application.h"
#include "EnemyZicZac.h"
#include "ModuleCollision.h"
#include "Animation.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"

EnemyZicZac::EnemyZicZac(int x,int y):Enemy(x,y){

	AnimZicZac.PushBack({ 32,161,32,27 });
	AnimZicZac.PushBack({ 64,161,32,27 });
	AnimZicZac.PushBack({ 96,161,32,27 });
	AnimZicZac.PushBack({ 128,161,32,27 });
	AnimZicZac.speed = 0.4f;
	AnimZicZac.loop = true;

	life = 1;
	animation = &AnimZicZac;
	collider = App->collision->AddCollider({ 0,0,27,22 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	
	original_y = y;

}


void EnemyZicZac::Move() {

	if (going_up)
	{
		if (wave > 1.0f)
			going_up = false;
		else
			wave += 0.1f;
	}
	else
	{
		if (wave < -1.0f)
			going_up = true;
		else
			wave -= 0.1f;
	}

	position.y = int(float(original_y) + (30.0f * sinf(wave)));
	position.x -= 0.9f;


}
