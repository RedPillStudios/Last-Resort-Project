#ifndef ModuleParticles_H
#define ModuleParticles_H

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleSound.h"

#include "SDL_mixer/include/SDL_mixer.h"

#define MAX_ACTIVE_PARTICLES 5000

struct SDL_Texture;

struct Particle {

	Animation Anim;
	uint fx = 0;
	iPoint Position;
	iPoint Speed;
	Uint32 Born = 0;
	Uint32 Life = 0;
	bool fx_played = false;

	Particle();
	Particle(const Particle &p);
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

	void AddParticle(const Particle &p, int x, int y, Uint32 delay = 0);
	
private:

	SDL_Texture *Sprites = nullptr;
	Particle *active[MAX_ACTIVE_PARTICLES];
	uint LastParticle = 0;

public:

	Particle ShootExplosion;
	Particle Laser;
	//Mix_Chunk *LaserSound;
};

#endif