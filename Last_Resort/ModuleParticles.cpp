#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles() {

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) {

		active[i] = nullptr;
	}
}

ModuleParticles::~ModuleParticles() {}


bool ModuleParticles::Start() {

	LOG("Loading Particles");
	Sprites = App->textures->Load("Images/Particles/Ship_Ball_Sprite.png");

	ShootExplosion.Anim.PushBack({ 82, 239, 12, 12 });
	ShootExplosion.Anim.PushBack({ 94, 241, 11, 9 });
	ShootExplosion.Anim.loop = false;
	ShootExplosion.Anim.speed = 0.3f;

	Laser.Anim.PushBack({ 115, 242, 15, 7 });
	Laser.Anim.loop = true;
	Laser.Anim.speed = 0.0f;
	Laser.fx = 1;
	Laser.Life = 2000;
	Laser.Speed.x = 5;

	return true;

}

bool ModuleParticles::CleanUp() {

	LOG("Unloading Particles");
	App->textures->Unload(Sprites);
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) {

		if (active[i] != nullptr) {

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

			App->render->Blit(Sprites, p->Position.x, p->Position.y, &(p->Anim.GetCurrentFrame()));
			if (p->fx_played = false) {

				p->fx_played = true;
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->Born = SDL_GetTicks() + delay;
			p->Position.x = x;
			p->Position.y = y;
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

	if (Life > 0) {

		if ((SDL_GetTicks() - Born) > Life) {
			ret = true;
		}
	}
	else {
		
		if (Anim.Finished()) {
			ret = false;
		}
	}

	Position.x += Speed.x;
	Position.y += Speed.y;

	if (collider != nullptr)
		collider->SetPos(Position.x, Position.y);

	return ret;

}