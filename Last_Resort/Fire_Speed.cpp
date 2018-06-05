#include "Fire_Speed.h"
#include "Application.h"
#include "ModuleCollision.h"
#include "Animation.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

FireSpeed::FireSpeed(int x, int y) : Enemy(x, y) {

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

void FireSpeed::Move() {
	position.x++;
	position.x = App->player->position.x-31;
	if(Fire.getCurrentFrame()<4)
		position.y = App->player->position.y - 10;
	if(Fire.getCurrentFrame()>=4){
		position.y = App->player->position.y;
	}
	if (Fire.Finished() == true) {
		touched = true;
	}
}
