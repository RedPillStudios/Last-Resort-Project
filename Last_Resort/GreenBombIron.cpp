#include "GreenBombIron.h"
#include "Application.h"
#include "ModuleCollision.h"
#include "Animation.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "Iron_Craw.h"


GreenBombIron::GreenBombIron(int x, int y):Enemy( x, y)
{
	
	GreenBombAnim.PushBack({ 235,0,18,17 });
	GreenBombAnim.PushBack({ 235,19,17,17 });
	GreenBombAnim.PushBack({ 236,37,17,17 });
	GreenBombAnim.PushBack({ 235,55,18,17 });
	GreenBombAnim.PushBack({ 236,72,17,18 });
	GreenBombAnim.PushBack({ 236,91,17,18 });
	GreenBombAnim.PushBack({ 234,109,18,17 });
	GreenBombAnim.PushBack({ 235,129,18,16 });
	GreenBombAnim.loop = true;



	Enemy::sprites = App->textures->Load("Images/Bosses/First_Mini_Boss_Sprite.png");

	life = 1;
	GreenBombAnim.speed = 0.09f;
	animation = &GreenBombAnim;

	collider = App->collision->AddCollider({ 0,0,18,17 }, COLLIDER_TYPE::COLLIDER_ENEMY_SHOT, (Module*)App->enemies);

}


void GreenBombIron::Move() 
{

	counter++;
	counter2++;

	if (position.y < App->MiniBoss->position.y+30) {
	
		if(counter<40)
		position.y-=0.1f;
		down_ = true;

	}
	else if (position.y > App->MiniBoss->position.y-30) {

		if(counter<40)
			position.y+=0.1f;
		up_ = true;
	}

	if (counter>=50 && (up_ || down_)) {
		PlayerPosition = App->player->position;
		position.x++;

		position.x += 0.015*(PlayerPosition.x - position.x);
		position.y += 0.015*(PlayerPosition.y - position.y);
	}

}

