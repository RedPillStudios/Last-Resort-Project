#include "Enemy_Tears.h"
#include "Application.h"
#include "ModuleCollision.h"
#include "Animation.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleSceneLvl1.h"
#include <time.h>
#include "cstdio"
Enemy_BossTears::Enemy_BossTears(int x, int y, bool powerUp) : Enemy(x, y){

	fly.PushBack({ 5,344,1,1 });
	fly.PushBack({ 14,344,2,1 });
	fly.PushBack({ 23,344,3,2 });
	fly.PushBack({ 33,343,4,3 });
	fly.PushBack({ 43,342,4,4 });
	fly.PushBack({ 53,342,4,4 });
	fly.PushBack({ 63,342,5,5 });
	fly.PushBack({ 72,342,6,5 });
	fly.PushBack({ 82,342,6,5 });
	fly.PushBack({ 92,341,6,6 });
	fly.PushBack({ 102,341,7,6 });
	fly.PushBack({ 111,341,8,7 });
	fly.PushBack({ 120,340,9,9 });
	fly.PushBack({ 130,339,10,10 });
	fly.PushBack({ 2,350,9,12 });
	fly.PushBack({ 15,350,11,13 });
	fly.PushBack({ 29,350,11,12 });
	fly.PushBack({ 43,350,13,13 });
	fly.PushBack({ 56,349,14,12 });

	
	Enemy::sprites = App->textures->Load("Images/General/Common_enemies_Sprite.png");

	fly.speed = 0.04f;
	fly.loop = true;
	animation = &fly;
	life = 5;
	score = 300;

	collider = App->collision->AddCollider({ 0, 0, 12, 12 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	original_y = y;
	PowerUp = powerUp;
	/*App->enemies->bigenemy = true;*/
}

void Enemy_BossTears::Move(){
	
	initialx = position.x;
	position.x -=0.6;
	if (position.x <= initialx && MovingDown == false) {
		position.x += 0.3;
		position.y -= velocityY;	
	}
	if (position.y <= Ylimit || MovingDown) {
		position.y += 2;
		MovingDown = true;
	}
	/*if (going_up) {
		wave++;
	}
	if (wave > 1) {
		going_up = false;
		wave--;
	}
	
	position.y = ((float)(original_y)+(69.0f * sinf(wave)));
	position.x -= 0.9f; */




	/*if (going_up )
	{
		if (wave > 1.0f)
			going_up = false;
		else
			wave += 0.05f;
	}
	else
	{
		if (wave < -1.0f) {
			going_up = true;
		
		}

		else 
			wave -= 0.05f;
	}

	position.y = ((float)(original_y)+(69.0f * sinf(wave)));
	position.x -= 0.9f;*/
}
