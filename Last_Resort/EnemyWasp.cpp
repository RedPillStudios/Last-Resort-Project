#include "Application.h"
#include "EnemyWasp.h"
#include "ModuleCollision.h"
#include "Animation.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"


EnemyWasp::EnemyWasp(int x, int y) : Enemy(x, y) {

	AnimWasp.PushBack({0, 178, 32, 15});
	AnimWasp.PushBack({ 0, 194, 32, 15 });
	AnimWasp.PushBack({ 0, 209, 32, 15 });
	AnimWasp.PushBack({ 0, 224, 32, 15 });
	AnimWasp.PushBack({ 0, 239, 32, 15 });
	Enemy::sprites = App->textures->Load("Images/General/Common_enemies_Sprite.png");

	score = 100;
	life = 1;

	AnimWasp.speed = 0.09f;
	AnimWasp.loop = true;
	animation = &AnimWasp;

	collider = App->collision->AddCollider({0,0,31,16}, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

// EnemyWasp::~EnemyWasp(){
//
//
//
//}
//

void EnemyWasp::Move() {

	(float)position.x -= 1.0f;
}