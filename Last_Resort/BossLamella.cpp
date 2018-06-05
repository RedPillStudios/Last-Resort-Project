#include "BossLamella.h"
#include "Application.h"
#include "ModuleCollision.h"
#include "Animation.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"

#include <math.h>


EnemyBossLamella::EnemyBossLamella(int x, int y, bool powerUp) : Enemy(x, y)
{

	Normal = App->textures->Load("Images/General/Common_enemies_Sprite.png");

	MovingAnim.PushBack ({ 128, 129, 31, 31 });
	MovingAnim.PushBack ({ 160, 130, 31, 30 });
	MovingAnim.PushBack ({ 193, 131, 30, 29 });
	MovingAnim.PushBack ({ 224, 130, 31, 30 });
	MovingAnim.speed = 0.05f;
	MovingAnim.loop = true;

	animation = &MovingAnim;
	life = 10;
	score = 300;
	
	HittedAnim.PushBack ({ 194, 162, 31, 30 });
	HittedAnim.loop = true;

	sprites = Normal;

	collider = App->collision->AddCollider({ 0, 0, 31, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	PowerUp = powerUp;

}

void EnemyBossLamella::Move() {

	if (hit == true) {
		counter++;
		if (counter > 10) {
			animation = &HittedAnim;
		}
		else {
			animation = &MovingAnim;
		}
		if (counter >= 20) {
			animation = &MovingAnim;
			counter = 0;
			hit = false;
		}
	}

	if (App->player->Dead == false) {
		PlayerPosition = App->player->position;
	}
	else {
		PlayerPosition = App->player2->positionp2;
	}

	position.x++;
	position.x += 0.01*(PlayerPosition.x - position.x);
	position.y += 0.01*(PlayerPosition.y - position.y);

}

void EnemyBossLamella::OnCollision(Collider *collider) {
	hit = true;
}