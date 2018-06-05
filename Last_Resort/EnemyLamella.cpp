#include "EnemyLamella.h"
#include "Application.h"
#include "ModuleCollision.h"
#include "Animation.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"

EnemyLamella::EnemyLamella(int x, int y, bool powerUp,ENEMY_TYPES type_) : Enemy(x, y) {

	type = type_;

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
	
	if(App->player->Dead == false){

		if (App->player->position.x > position.x)
			sprites = App->textures->Load("Images/General/Common_enemies_SpriteFlipped.png");
		else
			sprites = App->textures->Load("Images/General/Common_enemies_Sprite.png");
	}
	else {

		if (App->player2->positionp2.x > position.x)
			sprites = App->textures->Load("Images/General/Common_enemies_SpriteFlipped.png");
		else
			sprites = App->textures->Load("Images/General/Common_enemies_Sprite.png");
	}


	

	lastPosX = App->player->position.x;
	lastPosY = App->player->position.y;

	life = 1;
	score = 100;
	LamellaAnim.speed = 0.3f;
	LamellaAnim.loop = true;
	animation = &Apearing;
	typeColl = COLLIDER_ENEMY;
	PowerUp = powerUp;

}

void EnemyLamella::Move(){

	position.x++;
	
	if (Apearing.Finished() == false) {

		if (App->player->Dead == false) {

			PlayerPosition = App->player->position;
		}
		else {
			PlayerPosition = App->player2->positionp2;
		}
		
	}
	PlayerPosition.x++;

	if (Apearing.Finished() == true&&reachPosition==false) {
		StartAttack++;
		changeCollider++;
		if (changeCollider == 1) {
			collider = App->collision->AddCollider({ 0,0,32,32 },typeColl, (Module*)App->enemies);
		}
		animation = &LamellaAnim;
		if (StartAttack >= 50) {
			position.x += 0.03*(PlayerPosition.x - position.x);
			position.y += 0.03*(PlayerPosition.y - position.y);
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
}
