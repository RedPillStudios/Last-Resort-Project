//#include "EnemyLamella.h"
//#include "Application.h"
//#include "ModuleCollision.h"
//#include "Animation.h"
//#include "ModuleEnemies.h"
//#include "ModulePlayer.h"
//#include "ModuleParticles.h"
//
//
//
//EnemyLamella::EnemyLamella(int x, int y, bool powerUp,fPoint toGo) : Enemy(x, y) {
//	
//	int countx = 0;
//	int county = 0;
//
//	for (int i = 0; i < 36; i++) {
//		Apearing.PushBack({countx,county,32,32});
//		countx += 32;
//		if (countx >= 256) {
//			countx = 0;
//			county += 32;
//		}
//	}
//
//	Arriving.PushBack({ 39,189,10,10 });
//	LamellaAnim.PushBack({0, 130, 31, 31});
//	LamellaAnim.PushBack({ 32, 129, 31, 31 });
//	LamellaAnim.PushBack({ 64, 130, 31, 30 });
//	LamellaAnim.PushBack({ 97, 131, 30, 29 }); //Have to make him appear
//
//	Enemy::sprites = App->textures->Load("Images/General/Common_enemies_Sprite.png");
//
//	lastPosX = App->player->position.x;
//	lastPosY = App->player->position.y;
//
//	life = 1;
//	score = 100;
//	LamellaAnim.speed = 1.0f;
//	LamellaAnim.loop = true;
//	animation = &Arriving;
//
//	PowerUp = powerUp;
//	collider = App->collision->AddCollider({0,0,32,32}, COLLIDER_TYPE::COLLIDER_NONE, (Module*)App->enemies);
//}
//
//void EnemyLamella::Move(){
//
//	//if (Apearing.Finished() == false) {
//	//	PlayerPosition = App->player->position;
//	//}
//
//	//if (Apearing.Finished() == true) {
//	//	//position.x++;
//	//	position.x -= 0.005*(PlayerPosition.x + position.x);
//	//	position.y -= 0.005*(PlayerPosition.y + position.y);
//	////
//	if (reachPosition == false) {
//		position.x--;
//	}
//	if (position == toGo) {
//		reachPosition = true;
//	}
//
//	//if (reachPosition == true) {
//	//	animation = &Apearing;
//	//}
//		//if (App->player->position.x <= position.x)
//		//	position.x++;
//
//		//else
//		//	position.x--;
//
//		//if (App->player->position.y >= position.y)
//		//	position.y++;
//		//else
//		//	position.y--;
//}
