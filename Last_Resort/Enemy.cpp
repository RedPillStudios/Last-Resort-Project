#include "Application.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"

Enemy::Enemy(int x, int y) : position((float)x,(float)y) {}

Enemy::~Enemy() {

	if (collider != nullptr)
		collider->to_delete = true;
}

const Collider *Enemy::GetCollider() const {

	return collider;
}

void Enemy::Draw(SDL_Texture *sprites) {

	if (collider != nullptr)
		collider->SetPos((int)position.x, (int)position.y);

	if (animation != nullptr)
		App->render->Blit(sprites, (int)position.x, (int)position.y, &(animation->GetCurrentFrame()));
}

void Enemy::OnCollision(Collider* collider)
{
	App->particles->AddParticle(App->particles->ShootExplosion, (int)position.x, (int)position.y);
}