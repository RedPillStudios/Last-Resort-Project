#include "Application.h"
#include "EnemyWasp.h"
#include "ModuleCollision.h"
#include "Animation.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"


EnemyWasp::EnemyWasp(int x, int y) : Enemy(x, y) {

	/*AnimWasp.PushBack({0, 178, 32, 15});
	AnimWasp.PushBack({ 0, 178, 32, 15 });
	AnimWasp.PushBack({ 0, 178, 32, 15 });
	AnimWasp.PushBack({ 0, 178, 32, 15 });
	AnimWasp.PushBack({ 0, 178, 32, 15 });

	animation = &AnimWasp;
	collider = App->collision->AddCollider({}, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	position.x -= 3;
	position.y = y;*/
}