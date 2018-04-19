
#include "Application.h"
#include "CarsToFast.h"
#include "ModuleCollision.h"
#include "Animation.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"




CarsToFast::CarsToFast(int x, int y): Enemy(x,y){

	Cars.PushBack({0,184,20,11});
	Cars.PushBack({20,184,20,11});
	Cars.PushBack({40,184,20,11});
	Cars.PushBack({60,184,20,11});

	Enemy::sprites= App->textures->Load("Images/General/Car_Sprites.png");

	Cars.loop = true;
	Cars.speed =0.09f;
	animation = &Cars;
	life = 1;
	score = 100;
	collider = App->collision->AddCollider({0,0,21,11 }, COLLIDER_TYPE::COLLIDER_CAR, (Module*)App->enemies);

}


void CarsToFast::Move() {


	(float)position.x+= 3.0f;


}