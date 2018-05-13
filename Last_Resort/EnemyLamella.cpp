#include "EnemyLamella.h"
#include "Application.h"
#include "ModuleCollision.h"
#include "Animation.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"



EnemyLamella::EnemyLamella(int x, int y, bool powerUp) : Enemy(x, y) {

	Enemy::sprites = App->textures->Load("Images/General/Common_enemies_Sprite.png");

	LamellaAnim.PushBack({0, 130, 31, 31});
	LamellaAnim.PushBack({ 32, 129, 31, 31 });
	LamellaAnim.PushBack({ 64, 130, 31, 30 });
	LamellaAnim.PushBack({ 97, 131, 30, 29 }); //Have to make him appear

	lastPosX = App->player->position.x;
	lastPosY = App->player->position.y;

	life = 1;
	score = 100;
	LamellaAnim.speed = 1.0f;
	LamellaAnim.loop = true;
	animation = &LamellaAnim;

	PowerUp = powerUp;
	collider = App->collision->AddCollider({}, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void EnemyLamella::Move(){

	while (position.x != lastPosX && position.y != lastPosY) {

		if (App->player->position.x <= position.x)
			position.x++;
		else
			position.x--;

		if (App->player->position.y >= position.y)
			position.y++;
		else
			position.y--;
	}
}
