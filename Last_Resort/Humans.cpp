#include "Humans.h"
#include "Application.h"
#include "ModuleCollision.h"
#include "Animation.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"


Humans::Humans(int x, int y): Enemy(x, y){

	HumanAnimation.PushBack({131,192,12,16});
	HumanAnimation.PushBack({ 147,194,12,11 });
	HumanAnimation.PushBack({ 163,193,14,14 });
	HumanAnimation.PushBack({ 179,192,13,15 });
	HumanAnimation.PushBack({ 193,195,15,9 });
	HumanAnimation.PushBack({211,194,12,12});
	HumanAnimation.PushBack({ 228,192,11,16 });
	HumanAnimation.PushBack({ 244,192,12,16 });


	Enemy::sprites = App->textures->Load("Images/General/Common_enemies_Sprite.png");

	HumanAnimation.loop = true;
	HumanAnimation.speed = 0.09f;
	
	
	animation = &HumanAnimation;

	Up = true;
}

void Humans::Move() {

	position.x++;
	if (Up) {
		position.y-=2;

		counter++;
	}

	if (counter >= 40) {
		Up = false;
		position.y+=2;

	}


}
