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
	AnimWasp.PushBack({ 0, 240, 32, 15 });
	AnimWasp.PushBack({ 0, 225, 32, 15 });
	
	AnimWasp.speed = 0.1f;

	animation = &AnimWasp;

	collider = App->collision->AddCollider({0,0,32,15}, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	position.x = SCREEN_WIDTH+30;
	position.y = y;
}
void EnemyWasp::Move() {
	position.y = 130;
	position.x -=2;
}
