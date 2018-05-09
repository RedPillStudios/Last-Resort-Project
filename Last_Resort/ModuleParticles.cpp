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
	Particle1 = App->textures->Load("Images/Particles/Ship_Ball_Sprite.png");
	Particle2 = App->textures->Load("Images/Particles/BossWeapons&parts_EnemyShip&structure_Multiple-effects-and-explosions_Sprites.png");
	Particle3= App->textures->Load("Images/Bosses/Boss_Stage1_Sprites.png");

	ImpactExplosionSound = App->sound->LoadChunk("Audio/General/007_Enemy_Explosion_Standard.wav");

	ShootExplosion.Anim.PushBack({ 82, 239, 12, 12 });
	ShootExplosion.Anim.PushBack({ 94, 241, 11, 9 });
	ShootExplosion.Anim.loop = false;
	ShootExplosion.Anim.speed = 0.3f;
	ShootExplosion.Sprites = Particle1;

	Laser.Anim.PushBack({ 115, 242, 15, 7 });
	Laser.Anim.speed = 0.0f;
	Laser.fx = 1;
	Laser.Life = 900;
	Laser.Speed.x = 13;
	Laser.Sprites = Particle1;

	ImpactExplosion.Anim.PushBack({ 315,369,16,16 });
	ImpactExplosion.Anim.PushBack({ 331,369,16,16 });
	ImpactExplosion.Anim.PushBack({ 347,369,16,16 });   //explosion
	ImpactExplosion.Anim.PushBack({ 363,369,16,16 });
	ImpactExplosion.Anim.speed = 0.3f;
	ImpactExplosion.Anim.loop = false;
	ImpactExplosion.Sprites = Particle1;
//---------------------------------------------------
	//pattern1
	MissilePower.Anim.PushBack({ 14,237,30,16 });
	MissilePower.Anim.PushBack({ 0,290,74,6 });
	MissilePower.Anim.PushBack({ 0,258,44,7 });
	MissilePower.Anim.PushBack({ 0,274,44,7 });//

	MissilePower.Anim.PushBack({ 14,237,30,16 });
	MissilePower.Anim.PushBack({ 0,290,74,6 });
	MissilePower.Anim.PushBack({ 0,258,44,7 });
	MissilePower.Anim.PushBack({ 0,274,44,7 });//

	MissilePower.Anim.PushBack({ 0,258,44,7 });
	MissilePower.Anim.PushBack({ 0,274,44,7 });
	
	MissilePower.Anim.speed = 0.1f;
	MissilePower.Speed.x = 4;
	MissilePower.Anim.loop = false;
	MissilePower.Life = 3000;
	MissilePower.Sprites = Particle1;
	//pattern2
	MissilePowerPatter2.Anim.PushBack({ 14,237,30,16 });
	MissilePowerPatter2.Anim.PushBack({ 0,290,74,6 });
	MissilePowerPatter2.Anim.PushBack({ 0,258,44,7 });
	MissilePowerPatter2.Anim.PushBack({ 0,274,44,7 });//

	MissilePowerPatter2.Anim.PushBack({ 0,258,44,7 });
	MissilePowerPatter2.Anim.PushBack({ 0,274,44,7 });
	MissilePowerPatter2.Anim.PushBack({ 14,237,30,16 });
	MissilePowerPatter2.Anim.PushBack({ 0,290,74,6 });

	MissilePowerPatter2.Anim.PushBack({ 0,258,44,7 });
	MissilePowerPatter2.Anim.PushBack({ 0,274,44,7 });//

	MissilePowerPatter2.Anim.speed = 0.1f;
	MissilePowerPatter2.Speed.x = 4;
	MissilePowerPatter2.Anim.loop = false;
	MissilePowerPatter2.Life = 3000;
	MissilePowerPatter2.Sprites = Particle1;

	//___________________________

	LaserBeam.Sprites = App->textures->Load("Images/Particles/Ship_Ball_Sprite.png");
	LaserBeam.Anim.PushBack({ 23,296,112,3 });
	LaserBeam.Anim.loop = true;
	LaserBeam.Anim.speed = 0.1;
	LaserBeam.Speed.x = 8;
	LaserBeam.Life = 1000;

	LaserBeamExplosion.Sprites = App->textures->Load("Images/Particles/Ship_Ball_Sprite.png");
	LaserBeamExplosion.Anim.PushBack({ 0,317,13,13 });
	LaserBeamExplosion.Anim.PushBack({ 0,334,27,9 });
	LaserBeamExplosion.Anim.PushBack({ 0,348,30,7 });
	LaserBeamExplosion.Anim.PushBack({ 0,369,31,5 });
	LaserBeamExplosion.Anim.PushBack({ 33,319,32,3 });
	LaserBeamExplosion.Anim.PushBack({ 33,329,32,3 });
	LaserBeamExplosion.Anim.PushBack({ 33,348,30,3 });
	LaserBeamExplosion.Anim.loop = false;
	LaserBeamExplosion.Anim.speed = 0.3;
	LaserBeamExplosion.Speed.x = 1;

	LaserBeamArea1.Sprites = App->textures->Load("Images/Particles/Ship_Ball_Sprite.png");
	LaserBeamArea1.Anim.PushBack({ 48,264 - 10,4,8 + 21 });  //264
	LaserBeamArea1.Anim.PushBack({ 57,261 - 5,6,15 + 15 });  //261
	LaserBeamArea1.Anim.PushBack({ 66,254,11,31 });  //254
	LaserBeamArea1.Anim.loop = false;
	LaserBeamArea1.Anim.speed = 0.3f;
	LaserBeamArea1.Speed.x = 2;

	LaserBeamArea2.Sprites = App->textures->Load("Images/Particles/Ship_Ball_Sprite.png");
	LaserBeamArea2.Anim.PushBack({ 65,337,16,47 });
	LaserBeamArea2.Anim.PushBack({ 85,337,20,47 });
	LaserBeamArea2.Anim.PushBack({ 106,337,20,47 });
	LaserBeamArea2.Anim.PushBack({ 129,337,20,47 });   //LASER AREA 1
	LaserBeamArea2.Anim.PushBack({ 151,337,20,47 });
	LaserBeamArea2.Anim.PushBack({ 166,337,17,47 });//____________________________
	LaserBeamArea2.Anim.loop = false;
	LaserBeamArea2.Anim.speed = 0.1;
	LaserBeamArea2.Speed.x = 2.0f;
	LaserBeamArea2.Life = 300;

	LaserBeamArea3.Sprites = App->textures->Load("Images/Particles/Ship_Ball_Sprite.png");
	LaserBeamArea3.Anim.PushBack({ 65,337,16,47 });
	LaserBeamArea3.Anim.loop = false;
	LaserBeamArea3.Anim.speed = 0.1;
	LaserBeamArea3.Speed.x = 8;
	LaserBeamArea3.Life = 1000;



	EnemyExplosion.Anim.PushBack({ 0, 396, 32, 32 });
	EnemyExplosion.Anim.PushBack({67, 396, 32, 32});
	EnemyExplosion.Anim.PushBack({100, 396, 32, 32 });
	EnemyExplosion.Anim.PushBack({ 132, 396, 32, 32 });
	EnemyExplosion.Anim.speed = 0.3f;
	EnemyExplosion.Anim.loop = false;
	EnemyExplosion.Sprites = Particle2;
	//Boss
	BossShoot.Sprites = Particle3;
	BossShoot.Anim.PushBack({ 129,256, 63, 32 });
	BossShoot.Anim.PushBack({ 194,260, 63, 32 });
	BossShoot.Anim.loop = true;
	BossShoot.Life = 1300;
	BossShoot.Speed.x = -2;
	BossShoot.Anim.speed = 0.1f;

	BossCoolDown.Sprites = Particle3;
	BossCoolDown.Anim.PushBack({ 63,311,56, 28 });
	BossCoolDown.Anim.PushBack({ 119,311,56, 28 });
	BossCoolDown.Anim.PushBack({ 175,311,56, 28 });
	BossCoolDown.Anim.PushBack({ 231,311,56, 28 });
	BossCoolDown.Anim.PushBack({ 288,311,55, 28 });
	BossCoolDown.Anim.PushBack({ 347,311,52, 28 });
	BossCoolDown.Anim.PushBack({ 407,311,48, 28 });
	BossCoolDown.Anim.PushBack({ 467,311,46, 28 });
	BossCoolDown.Anim.loop = false;
	BossCoolDown.Speed.x = 1;
	BossCoolDown.Anim.speed = 0.2f;

	BossShootExplosion.Sprites = Particle3;
	BossShootExplosion.Anim.PushBack({ 448, 255, 64, 56 });
	BossShootExplosion.Anim.PushBack({ 384, 255, 64, 56 });
	BossShootExplosion.Anim.speed = 0.15f;

	HOU_Shot.Anim.PushBack({ 117,250,13,13 });

	//HOU_Shot.Anim.PushBack({117,263,13,13});
	HOU_Shot.Anim.speed = 0.2f;
	HOU_Shot.Anim.loop = true;
	HOU_Shot.Sprites = Particle1;
	HOU_Shot.Life = 2200;
	

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

	App->sound->UnloadChunks(ImpactExplosionSound);

	App->textures->Unload(Particle1);
	App->textures->Unload(Particle2);
	App->textures->Unload(Particle3);
	App->textures->Unload(LaserBeam.Sprites);
	App->textures->Unload(ImpactExplosion.Sprites);
	App->textures->Unload(LaserBeamExplosion.Sprites);
	App->textures->Unload(LaserBeamArea1.Sprites);
	App->textures->Unload(LaserBeamArea2.Sprites);
	App->textures->Unload(LaserBeamArea3.Sprites);
		

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
		// DON'T DESTROY LASERBEAM WHEN COLLIDES
		
		if (active[i] != nullptr && active[i]->collider == c1 && c1->type == COLLIDER_PLAYER_LASERBEAM_SHOT) {

			if (c2->type == COLLIDER_ENEMY || c2->type == COLLIDER_WALL)
				AddParticle(ImpactExplosion, active[i]->Position.x, active[i]->Position.y);
			if (c2->type == COLLIDER_ENEMY) {
				Mix_PlayChannel(-1, ImpactExplosionSound, 0);

				//AREAS DISSAPEARING JUST 1 TIME!!!
		
				if (active[i]->TimesCollided == 0 ) {
					active[i]->TimesCollided = 1;
					
					AddParticle(LaserBeamArea3, active[i]->Position.x + 90, active[i]->Position.y - 18, COLLIDER_NONE, 100 - 30);
					AddParticle(LaserBeamArea3, active[i]->Position.x + 90, active[i]->Position.y - 18, COLLIDER_NONE, 150 - 30);
					AddParticle(LaserBeamArea3, active[i]->Position.x + 90, active[i]->Position.y - 18, COLLIDER_NONE, 200 - 30);
					
					AddParticle(LaserBeamArea2, active[i]->Position.x + 160, active[i]->Position.y - 18, COLLIDER_NONE, 250 - 30);
				}
				
				////_______
				AddParticle(EnemyExplosion, active[i]->Position.x, active[i]->Position.y);
				AddParticle(EnemyExplosion, active[i]->Position.x + 80, active[i]->Position.y - 2, COLLIDER_NONE, 200);
				AddParticle(EnemyExplosion, active[i]->Position.x - 80, active[i]->Position.y + 3, COLLIDER_NONE, 200);
			}
			break;
		}

		// Always destroy particles that collide AND AREN`T LASSER BEAM
		if (active[i] != nullptr && active[i]->collider == c1 && c1->type != COLLIDER_PLAYER_LASERBEAM_SHOT) {
			
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
			App->sound->UnloadChunks(ImpactExplosionSound);
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

		if (((int)SDL_GetTicks() - (int)Born) > (int)Life)
			ret = false;
	}
	else
		if (Anim.Finished())
			ret = false;

	if (collider != nullptr && (collider->type == COLLIDER_PLAYER_SHOT || collider->type == COLLIDER_PLAYER_SHOT2) && Position.x >= App->scene1background->position_max_limit)
			ret = false;
	
	if (SDL_GetTicks() >= Born) {

		Position.x += Speed.x;
		Position.y += Speed.y;

		if (collider != nullptr)
			collider->SetPos(Position.x, Position.y);
	}

	return ret;

}