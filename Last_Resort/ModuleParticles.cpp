#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleSceneLvl1.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles() {

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) {

		active[i] = nullptr;
	}
}

ModuleParticles::~ModuleParticles() {}

bool ModuleParticles::Start() {

	LOG("Loading Particles");
	 
	ImpactExplosionSound = App->sound->LoadChunk("Audio/General/007_Enemy_Explosion_Standard.wav");

	ShootExplosion.Anim.PushBack({ 82, 239, 12, 12 });
	ShootExplosion.Anim.PushBack({ 94, 241, 11, 9 });
	ShootExplosion.Anim.loop = false;
	ShootExplosion.Anim.speed = 0.3f;
	ShootExplosion.Sprites= App->textures->Load("Images/Particles/Ship_Ball_Sprite.png");

	Laser.Anim.PushBack({ 115, 242, 15, 7 });
	Laser.Anim.speed = 0.0f;
	Laser.fx = 1;
	Laser.Life = 1100;
	Laser.Speed.x = 5;
	Laser.Sprites = App->textures->Load("Images/Particles/Ship_Ball_Sprite.png");

	ImpactExplosion.Anim.PushBack({ 315,369,16,16 });
	ImpactExplosion.Anim.PushBack({ 331,369,16,16 });
	ImpactExplosion.Anim.PushBack({ 347,369,16,16 });   //explosion
	ImpactExplosion.Anim.PushBack({ 363,369,16,16 });
	ImpactExplosion.Anim.speed = 0.3f;
	ImpactExplosion.Anim.loop = false;
	ImpactExplosion.Sprites= App->textures->Load("Images/Particles/Ship_Ball_Sprite.png");

	EnemyExplosion.Anim.PushBack({ 0, 396, 32, 32 });
	EnemyExplosion.Anim.PushBack({67, 396, 32, 32});
	EnemyExplosion.Anim.PushBack({100, 396, 32, 32 });
	EnemyExplosion.Anim.PushBack({ 132, 396, 32, 32 });
	
	
	EnemyExplosion.Anim.speed = 0.3f;
	EnemyExplosion.Anim.loop = false;
	EnemyExplosion.Sprites= App->textures->Load("Images/Particles/BossWeapons&parts_EnemyShip&structure_Multiple-effects-and-explosions_Sprites.png");


	return true;

}

bool ModuleParticles::CleanUp() {

	LOG("Unloading Particles");
	
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) {

		if (active[i] != nullptr) {
			App->textures->Unload(active[i]->Sprites);
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

update_status ModuleParticles::Update() {

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) {

		Particle *p = active[i];

		if (p == nullptr) {
			continue;
		}

		if (p->Update() == false) {

			delete p;
			active[i] = nullptr;
		}

		else if (SDL_GetTicks() >= p->Born) {

			App->render->Blit(p->Sprites, p->Position.x, p->Position.y, &(p->Anim.GetCurrentFrame()));
			if (p->fx_played = false) {

				p->fx_played = true;
			}
		}
	}
	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay) {

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) {
		if (active[i] == nullptr) {

			Particle* p = new Particle(particle);
			p->Born = SDL_GetTicks() + delay;
			p->Position.x = x;
			p->Position.y = y;
			p->Sprites = particle.Sprites;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->Anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1) {

			if (c2->type == COLLIDER_ENEMY || c2->type == COLLIDER_WALL)
					AddParticle(ImpactExplosion,active[i]->Position.x, active[i]->Position.y);
			if (c2->type == COLLIDER_ENEMY) {
					Mix_PlayChannel(-1, ImpactExplosionSound, 0);
					AddParticle(EnemyExplosion, active[i]->Position.x, active[i]->Position.y);
					AddParticle(EnemyExplosion, active[i]->Position.x + 3, active[i]->Position.y -2, COLLIDER_NONE, 200);
					AddParticle(EnemyExplosion, active[i]->Position.x - 3, active[i]->Position.y +2, COLLIDER_NONE, 200);
				}
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}

Particle::Particle() {

	Position.SetToZero();
	Speed.SetToZero();
}

Particle::Particle(const Particle &p) :
	Anim(p.Anim), Position(p.Position), Speed(p.Speed),
	fx(p.fx), Born(p.Born), Life(p.Life) {}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update() {

	bool ret = true;

	if (Life > 0)
	{
		if ((SDL_GetTicks() - Born) > Life)
			ret = false;
	}
	else
		if (Anim.Finished())
			ret = false;

	if (collider != nullptr && collider->type == COLLIDER_PLAYER_SHOT && Position.x >= App->scene1background->position_max_limit)
			ret = false;
	

	Position.x += Speed.x;
	Position.y += Speed.y;

	if (collider != nullptr)
		collider->SetPos(Position.x, Position.y);

	return ret;

}