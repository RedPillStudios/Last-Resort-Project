
#include "Application.h"
#include "CarsToFast.h"
#include "ModuleCollision.h"
#include "Animation.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include <time.h>
#include <iostream>




CarsToFast::CarsToFast(int x, int y): Enemy(x,y){
	
	randomColorCars = rand() % 3 + 1;
	for (int i = 0; i < 100; i++) {
		LOG("%u", rand());


	}

	CarRed.PushBack({ 0,184,21,11 });
	CarRed.PushBack({ 21,184,21,11 });
	CarRed.PushBack({ 42,184,21,11 });
	CarRed.PushBack({ 63,184,21,11 });
	CarRed.loop = true;
	CarRed.speed = 0.09f;

	CarYellow.PushBack({ 0,198,21,11 });
	CarYellow.PushBack({ 21,198,21,11 });
	CarYellow.PushBack({ 42,198,21,11 });
	CarYellow.PushBack({ 63,198,21,11 });
	CarYellow.speed = 0.09f;


	CarBlue.PushBack({ 0,212,21,11 });
	CarBlue.PushBack({ 21,212,21,11 });
	CarBlue.PushBack({ 42,212,21,11 });
	CarBlue.PushBack({ 63,212,21,11 });
	CarBlue.speed = 0.09f;

	Enemy::sprites = App->textures->Load("Images/General/Car_Sprites.png");


	if (randomColorCars == 3) {
		animation = &CarRed;
	}
	else if (randomColorCars == 2) {
		animation = &CarBlue;
	}
	else if (randomColorCars == 1) {
		animation = &CarYellow;
	}

	life = 1;
	score = 100;
	collider = App->collision->AddCollider({ 0,0,21,11 }, COLLIDER_TYPE::COLLIDER_CAR, (Module*)App->enemies);

}


void CarsToFast::Move() {


	(float)position.x+= 3.0f;


}