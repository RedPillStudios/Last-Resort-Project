#include "Application.h"
#include "EnemyRhino.h"
#include "ModuleCollision.h"
#include "Animation.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"

Enemy_Rhino::Enemy_Rhino(int x, int y, bool powerUp,ENEMY_TYPES type_) : Enemy(x, y)
{
	type = type_;

	fly.PushBack({ 64,211,48,45 });
	fly.PushBack({ 112,211,48,45 });
	fly.PushBack({ 160,211,48,45 });
	fly.PushBack({ 208,211,48,45 });
	fly.PushBack({ 160,211,48,45 });
	fly.PushBack({ 112,211,48,45 });
	fly.PushBack({ 64,211,48,45 });
	counter = 0;

	sprites = App->textures->Load("Images/General/Common_enemies_Sprite.png");
	Normal = App->textures->Load("Images/General/Common_enemies_Sprite.png");
	Damaged = App->textures->Load("Images/General/Common_enemies_Damaged_Sprite.png");

	fly.speed = 0.04f;
	fly.loop = true;
	animation = &fly;
	life = 5; 
	score = 300;

	collider = App->collision->AddCollider({ 0, 0, 48, 45 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	original_y = y;
	PowerUp = powerUp;
	/*App->enemies->bigenemy = true;*/
}

void Enemy_Rhino::Move()
{

	if (hit == true) {
		counter++;
		if (counter % 2 == 0) {
			sprites = Damaged;
		}
		else {
			sprites = Normal;
		}
		if (counter >= 30) {
			sprites = Normal;
			counter = 0;
			hit = false;
		}
	}

	if (going_up)
	{
		if (wave > 1.0f)
			going_up = false;
		else
			wave += 0.05f;
	}
	else
	{
		if (wave < -1.0f)
			going_up = true;
		else
			wave -= 0.05f;
	}

	position.y = ((float)(original_y) + (69.0f * sinf(wave)));
	position.x -= 0.9f;
}
void Enemy_Rhino::OnCollision(Collider *collider) {
	hit = true;
}
