#include "Application.h"
#include "EnemyBEE.h"
#include "ModuleCollision.h"
#include "Animation.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include <math.h>

Enemy_Bee::Enemy_Bee(int x, int y, bool powerUp) : Enemy(x, y)
{

	Front.PushBack({0 ,0,48,45 });
	Front.PushBack({ 48 ,0,48,45 });

	Front_left.PushBack({ 96,0,48,45 });
	Front_left.PushBack({ 144,0,48,45 });
	Front_left.speed = 0.05f;

	Front_mid_Left.PushBack({192 ,0,48,45 });
	Front_mid_Left.PushBack({ 0 ,45,48,45 });
	Front_mid_Left.speed = 0.05f;

	After_Left.PushBack({ 48,45,48,45 });
	After_Left.PushBack({ 96,45,48,45 });

	Left.PushBack({144,45,48,45 });
	Left.PushBack({ 192,45,48,45 });

	Before_Left.PushBack({ 0,90,48,45 });
	Before_Left.PushBack({ 48,90,48,45 });

	mid_Left.PushBack({ 96,90,48,45 });

	Back_Left.PushBack({ 144,90,48,45 });
	Back_Left.PushBack({ 192,90,48,45 });

	Back.PushBack({ 0,135,48,45 });
	Back.PushBack({ 48,135,48,45 });

	Back_Right.PushBack({ 96,135,48,45 });
	Back_Right.PushBack({ 144,135,48,45 });

	Back_mid_Right.PushBack({ 192,135,48,45 });


	Before_Right.PushBack({0 ,180,48,45 });
	Before_Right.PushBack({ 48 ,180,48,45 });

	Right.PushBack({ 96,180,48,45 });
	Right.PushBack({ 144,180,48,45 });

	After_Right.PushBack({ 192,180,48,45 } );
	After_Right.PushBack({ 0,225,48,45 });

	Front_mid_Right.PushBack({ 48,225,48,45 });
	Front_mid_Right.PushBack({ 96,225,48,45 });

	Front_Right.PushBack({ 144,225,48,45 });
	Front_Right.PushBack({192,225,48,45 });

	Enemy::sprites = App->textures->Load("Images/General/Hunter_Sprite.png");

	Front.speed = 0.05f;
	Front.loop = true;
	animation = &Front;
	life = 5;
	score = 300;

	collider = App->collision->AddCollider({ 0, 0, 48, 45 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	PowerUp = powerUp;

}

void Enemy_Bee::Move() {

	radians = atan2((position.y-PlayerPosition.y), (position.x-PlayerPosition.x));
	radians2 = atan2((PlayerPosition.y+2-position.y), (PlayerPosition.x+6-position.x));

	angle2 = radians2*(180 / PI);
	if (radians2 < 0) {
		angle2 += 360;
	}

	angle = radians*(180 / PI);
	if (radians < 0) {
		angle += 360;
	}
	

	LOG("Angle is %i", angle);

	if (angle <= 10 && angle >= 0) {
		animation = &Left;
	}
	if (angle <= 34 && angle > 10) {
		animation = &Before_Left;
	}
	if (angle <= 55 && angle > 34) {
		animation = &mid_Left;
	}	
	if (angle <= 87 && angle > 55) {
		animation = &Back_Left;
	}
	if (angle <= 102 && angle > 87) {
		animation = &Back;
	}
	if (angle <= 122 && angle > 102) {
		animation = &Back_Right;
	}
	if (angle <= 145 && angle > 122) {
		animation = &Back_mid_Right;
	}
	if (angle <= 167 && angle > 145) {
		animation = &Before_Right;
	}	
	if (angle <= 190 && angle > 167) {
		animation = &Right;
	}
	if (angle <= 212 && angle > 190) {
		animation = &After_Right;
	}
	if (angle <=235  && angle > 212) {
		animation = &Front_mid_Right;
	}
	if (angle <= 257 && angle > 235) {
		animation = &Front_Right;
	}
	if (angle <= 280 && angle > 257) {
		animation = &Front;
	}
	if (angle <= 302 && angle > 280) {
		animation = &Front_left;
	}
	if (angle <= 325 && angle > 302) {
		animation = &Front_mid_Left;
	}
	if (angle <= 350 && angle > 325) {
		animation = &After_Left;
	}
	if (angle <= 360 && angle > 350) {
		animation = &Left;
	}



	counter++;

	if (counter >= 70) {

		App->particles->BeeShot.Speed.x = 3* (cos(angle2*PI/180));
		App->particles->BeeShot.Speed.x++;
		App->particles->BeeShot.Speed.y = 3 * (sin(angle2*PI/180));
		App->particles->AddParticle(App->particles->BeeShot, position.x+20, position.y,COLLIDER_TYPE::COLLIDER_ENEMY_SHOT);
		
		counter = 0;
	}

	PlayerPosition = App->player->position;
	position.x++;
	position.x += 0.02*(PlayerPosition.x - position.x);
	position.y += 0.02*(PlayerPosition.y - position.y);



}

