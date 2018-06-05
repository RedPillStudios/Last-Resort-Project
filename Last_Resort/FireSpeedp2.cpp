#include "FireSpeedp2.h"
#include "Application.h"
#include "ModuleCollision.h"
#include "Animation.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer2.h"

FireSpeedp2::FireSpeedp2(int x, int y) : Enemy(x, y) {

	Fire.PushBack({ 0,0,32,32 });
	Fire.PushBack({ 32,0,32,32 });
	Fire.PushBack({ 64,0,32,32 });
	Fire.PushBack({ 96,0,32,32 });
	Fire.PushBack({ 0,32,32,15 });
	Fire.PushBack({ 32,32,32,15 });
	Fire.PushBack({ 64,32,32,15 });
	Fire.PushBack({ 96,32,32,15 });
	Fire.PushBack({ 0,49,32,15 });
	Fire.PushBack({ 32,49,32,15 });
	Fire.speed = 0.15f;


	Enemy::sprites = App->textures->Load("Images/General/PowerUps_Sprite.png");

	Fire.loop = false;

	life = 1;
	animation = &Fire;
}

void FireSpeedp2::Move() {
	position.x++;
	position.x = App->player2->positionp2.x - 31;
	if (Fire.getCurrentFrame()<4)
		position.y = App->player2->positionp2.y - 10;
	if (Fire.getCurrentFrame() >= 4) {
		position.y = App->player2->positionp2.y;
	}
	if (Fire.Finished() == true) {
		touched = true;
	}
}
