#ifndef ModuleParticles_H
#define ModuleParticles_H

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleSound.h"
#include "ModuleCollision.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "SDL/include/SDL.h"

#define MAX_ACTIVE_PARTICLES 700


struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

enum TYPE {
	NO_PARTICLE,
	PARTICLE_1,
	PARTICLE_2
	
};

struct Particle {

	Collider* collider = nullptr;
	Animation Anim;
	uint fx = 0;
	iPoint Position;
	iPoint Speed;
	Uint32 Born = 0;
	Uint32 Life = 0;
	bool fx_played = false;
	TYPE Particle_Type=NO_PARTICLE;
	uint TimesCollided = 0;


	SDL_Texture *Sprites = nullptr;

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

	Particle *active[MAX_ACTIVE_PARTICLES];

public:

	Particle ShootExplosion;
	Particle Laser;
	Particle ImpactExplosion;
	Particle EnemyExplosion;
	Particle Laser2;
	Particle ShootExplosionLaser2; // estas dos son para el segundo tipo de disparo
	Particle HOU_Shot;
	Particle HOU_Shot_p2;
	Particle MissilePower;
	Particle MissilePowerPatter2;
	Particle FogExplosion; 
	Particle FogExplosionCars;
	Particle MaleTears;
	Particle GreenBombAnimDestr;

	Particle LaserBeam;
	Particle LaserBeamExplosion;
	Particle LaserBeamArea1;
	Particle LaserBeamArea2;
	Particle LaserBeamArea3; 
	Particle Red_ThrowBall_pl1;
	Particle Blue_ThrowBall_pl1;
	Particle Red_ThrowBall_pl2;
	Particle Blue_ThrowBall_pl2;


	Particle HipopotamoBomba;
	Particle HipopotamoBomba2;


	Particle BeeShot;
	Particle TankBigShoot;

	SDL_Texture *particle0 = nullptr;
	SDL_Texture *Particle1 = nullptr;
	SDL_Texture *Particle2 = nullptr;
	SDL_Texture *Particle3 = nullptr;
	SDL_Texture *Particle4 = nullptr;
	SDL_Texture *Particle5 = nullptr;
	SDL_Texture *Particle6 = nullptr;
	SDL_Texture*particleMiniBoss = nullptr;
	SDL_Texture*Explosion_Texture = nullptr;


	//Boss Shoot
	Particle BossShoot;
	Particle BossCoolDown;
	Particle BossShootExplosion;
	

	Mix_Chunk *ImpactExplosionSound;
	Mix_Chunk *ImpactExplosionSound2;

	int randomExplosionSound;

	uint Enemies_Weapon = 0;
	uint Enemies_Speed = 0;

	//this  function is to store info to destroy particles when it is necessary.
	uint Destroy1 = 999999;
	uint Destroy2 = 999999;
	uint Destroy3 = 999999;



};

#endif