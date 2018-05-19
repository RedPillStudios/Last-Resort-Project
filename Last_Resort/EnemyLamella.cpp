#include "EnemyLamella.h"
#include "Application.h"
#include "ModuleCollision.h"
#include "Animation.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"



EnemyLamella::EnemyLamella(int x, int y, bool powerUp) : Enemy(x, y) {

	int countx = 0;
	int county = 0;

	int countx2 = 96;
	int county2 = 128;
	for (int i = 36; i > 0; --i) {
		Despawing.PushBack({ countx2,county2,32,32 });
		countx2 -= 32;
		if (countx2 <= 0) {
			countx2 = 256;
			county2 -= 32;
		}
	}
	Despawing.speed = 0.4f;
	Despawing.loop = false;

	for (int i = 0; i < 36; ++i) {
		Apearing.PushBack({countx,county,32,32});
		countx += 32;
		if (countx >= 256) {
			countx = 0;
			county += 32;
		}
	}
	Apearing.speed = 0.2f;
	Apearing.loop = false;
	Arriving.PushBack({ 39,189,10,10 });
	LamellaAnim.PushBack({0, 130, 31, 31});
	LamellaAnim.PushBack({ 32, 129, 31, 31 });
	LamellaAnim.PushBack({ 64, 130, 31, 30 });
	LamellaAnim.PushBack({ 97, 131, 30, 29 }); //Have to make him appear

	sprites = App->textures->Load("Images/General/Common_enemies_Sprite.png");

	lastPosX = App->player->position.x;
	lastPosY = App->player->position.y;

	life = 1;
	score = 100;
	LamellaAnim.speed = 0.3f;
	LamellaAnim.loop = true;
	animation = &Apearing;
	type = COLLIDER_ENEMY;
	PowerUp = powerUp;
	//collider = App->collision->AddCollider({0,0,32,32}, type, (Module*)App->enemies);
}

void EnemyLamella::Move(){
	position.x++;
	
	if (Apearing.Finished() == false) {
		PlayerPosition = App->player->position;
		
	}
	PlayerPosition.x++;

	if (Apearing.Finished() == true&&reachPosition==false) {
		StartAttack++;
		changeCollider++;
		if (changeCollider == 1) {
			collider = App->collision->AddCollider({ 0,0,32,32 },type, (Module*)App->enemies);
		}
		animation = &LamellaAnim;
		if (StartAttack >= 50) {
			position.x += 0.013*(PlayerPosition.x - position.x);
			position.y += 0.013*(PlayerPosition.y - position.y);
			if ((position.x < PlayerPosition.x + 25 && position.x > PlayerPosition.x - 25) && (position.y<PlayerPosition.y + 25 && position.y>PlayerPosition.y - 25)) {
				animation = &Despawing;
				collider->changeCollider(COLLIDER_TYPE::COLLIDER_NONE);
				reachPosition = true;
			}
		}
		}
	if (reachPosition&&Despawing.Finished()==true) {
		reached = true;
	}
	
/*  if (reachPosition == false) 
  	  position.x--;
	
  	if (position == toGo) 
	  	reachPosition = true;

	  if (reachPosition == true)
	  	animation = &Apearing;

		if (App->player->position.x <= position.x)
			position.x++;

		else
			position.x--;

		if (App->player->position.y >= position.y)
			position.y++;
		else
			position.y--; */
}
