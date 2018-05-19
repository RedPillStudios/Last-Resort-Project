#include "Application.h"
#include "EnemyBEE.h"
#include "ModuleCollision.h"
#include "Animation.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

Enemy_Bee::Enemy_Bee(int x, int y, bool powerUp) : Enemy(x, y)
{

	Front.PushBack({0 ,0,48,45 });
	Front.PushBack({ 48 ,0,48,45 });

	Front_left.PushBack({ 96,0,48,45 });
	Front_left.PushBack({ 144,0,48,45 });

	Front_mid_Left.PushBack({192 ,0,48,45 });
	Front_mid_Left.PushBack({ 0 ,45,48,45 });

	After_Left.PushBack({ 48,45,48,45 });
	After_Left.PushBack({ 96,45,48,45 });

	Left.PushBack({144,45,48,45 });
	Left.PushBack({ 192,45,48,45 });

	Before_Left.PushBack({ 0,90,48,45 });
	Before_Left.PushBack({ 44,90,48,45 });

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

	After_Right.PushBack({ 192,180,48,45 });
	After_Right.PushBack({ 0,225,48,45 });

	Front_mid_Right.PushBack({ 44,225,48,45 });
	Front_mid_Right.PushBack({ 96,225,48,45 });

	Front_Right.PushBack({ 144,225,48,45 });
	Front_Right.PushBack({192,225,48,45 });

	Enemy::sprites = App->textures->Load("Images/General/Hunter_Sprite.png");

	Front.speed = 0.04f;
	Front.loop = true;
	animation = &Front;
	life = 5;
	score = 300;

	collider = App->collision->AddCollider({ 0, 0, 48, 45 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	PowerUp = powerUp;
	/*App->enemies->bigenemy = true;*/
}

void Enemy_Bee::Move() {
	PlayerPosition = App->player->position;
	position.x++;
	position.x += 0.02*(PlayerPosition.x - position.x);
	position.y += 0.02*(PlayerPosition.y - position.y);



}

