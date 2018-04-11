#ifndef ModuleParticles_H
#define ModuleParticles_H

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleSound.h"
#include "ModuleCollision.h"

#include "SDL_mixer/include/SDL_mixer.h"

#define MAX_ACTIVE_PARTICLES 5000

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Particle {

	Collider* collider = nullptr;
	Animation Anim;
	uint fx = 0;
	iPoint Position;
	iPoint Speed;
	Uint32 Born = 0;
	Uint32 Life = 0;
	bool fx_played = false;

	Particle();
	Particle(const Particle &p);
	~Particle();
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

public:

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);
	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);

private:

	SDL_Texture *Sprites = nullptr;
	Particle *active[MAX_ACTIVE_PARTICLES];

public:

	Particle ShootExplosion;
	Particle Laser;
};

#endif