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
#include <cstdlib>
#include <math.h>

ModuleParticles::ModuleParticles() {

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) {

		active[i] = nullptr;
	}


//	srand(2);
}

ModuleParticles::~ModuleParticles() {}

bool ModuleParticles::Start() {
	
	
	LOG("Loading Particles");
	particle0 = App->textures->Load("Images/Player/Ship&Ball_Sprite.png");
	Particle1 = App->textures->Load("Images/Particles/Ship_Ball_Sprite.png");
	Particle2 = App->textures->Load("Images/Particles/BossWeapons&parts_EnemyShip&structure_Multiple-effects-and-explosions_Sprites.png");
	Particle3 = App->textures->Load("Images/Bosses/Boss_Stage1_Sprites.png");
	Particle4 = App->textures->Load("Images/Player/Charge_Ball.png");
	Particle5 = App->textures->Load("Images/Particles/Explosion.png");
	Particle6 = App->textures->Load("Images/Bosses/First_Mini_Boss_Sprite.png");
	Explosion_Texture = App->textures->Load("Images/Particles/Explosion_Good.png");
//	Particle6 = App->textures->Load("Images/Bosses/First_Mini_Boss_Sprite.png");

	ImpactExplosionSound = App->sound->LoadChunk("Audio/General/007_Enemy_Explosion_Standard.wav");
	ImpactExplosionSound2 = App->sound->LoadChunk("Audio/General/Explosion2.wav");

	Mix_VolumeChunk(ImpactExplosionSound,MIX_MAX_VOLUME/2.5f);
	Mix_VolumeChunk(ImpactExplosionSound2, MIX_MAX_VOLUME / 2);

	//BOOOOOOOOOOOOOOOOOOOOOOOOOOOMBAAAA un movimiento muy sexy: se-xy, un movimiento muy sensual: sen-sual
	HipopotamoBomba.Anim.PushBack({ 0, 306, 16, 6 });
	HipopotamoBomba.Anim.PushBack({ 17, 303, 15, 10 });
	HipopotamoBomba.Anim.PushBack({ 34, 301, 10, 15 });

	HipopotamoBomba.Anim.loop = false;
	HipopotamoBomba.Anim.speed = 0.1f;
	HipopotamoBomba.Sprites = Particle1;
	HipopotamoBomba.Life = 1200;
	HipopotamoBomba.Speed.y = 3;
	HipopotamoBomba.Speed.x = (HipopotamoBomba.Position.x ^ 2);

	HipopotamoBomba2.Anim.PushBack({ 0, 306, 16, 6 });
	HipopotamoBomba2.Anim.PushBack({ 45, 302, 15, 10 });
	HipopotamoBomba2.Anim.PushBack({ 62, 301, 11, 15 });

	HipopotamoBomba2.Anim.loop = false;
	HipopotamoBomba2.Anim.speed = 0.1f;
	HipopotamoBomba2.Sprites = Particle1;
	HipopotamoBomba2.Life = 1200;
	HipopotamoBomba2.Speed.y = -(2.5f);
	HipopotamoBomba2.Speed.x = (HipopotamoBomba2.Position.x ^ 2);


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
	MissilePower.Anim.PushBack({ 0,384,74,16 });
	MissilePower.Anim.PushBack({ 0,400,74,16 });
	MissilePower.Anim.PushBack({ 0,416,74,16 });
	MissilePower.Anim.PushBack({ 0,432,74,16 });//

	
	MissilePower.Anim.speed = 0.3f;
	MissilePower.Anim.loop = true;
	MissilePower.Speed.x = 4;
	MissilePower.Life = 3000;
	MissilePower.Sprites = particle0;

	////pattern2
	//MissilePowerPatter2.Anim.PushBack({ 14,237,30,16 });
	//MissilePowerPatter2.Anim.PushBack({ 0,290,74,6 });
	//MissilePowerPatter2.Anim.PushBack({ 0,258,44,7 });
	//MissilePowerPatter2.Anim.PushBack({ 0,274,44,7 });//

	//MissilePowerPatter2.Anim.PushBack({ 0,258,44,7 });
	//MissilePowerPatter2.Anim.PushBack({ 0,274,44,7 });
	//MissilePowerPatter2.Anim.PushBack({ 14,237,30,16 });
	//MissilePowerPatter2.Anim.PushBack({ 0,290,74,6 });

	//MissilePowerPatter2.Anim.PushBack({ 0,258,44,7 });
	//MissilePowerPatter2.Anim.PushBack({ 0,274,44,7 });//

	//MissilePowerPatter2.Anim.speed = 0.1f;
	//MissilePowerPatter2.Speed.x = 4;
	//MissilePowerPatter2.Anim.loop = false;
	//MissilePowerPatter2.Life = 3000;
	//MissilePowerPatter2.Sprites = Particle1;

	//___________________________

	LaserBeam.Sprites = Particle1; //App->textures->Load("Images/Particles/Ship_Ball_Sprite.png");
	LaserBeam.Anim.PushBack({ 23,296,66,3 });
	LaserBeam.Anim.loop = true;
	LaserBeam.Anim.speed = 0.1;
	LaserBeam.Speed.x = 8;
	LaserBeam.Life = 1000;

	LaserBeamExplosion.Sprites = Particle1;
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

	LaserBeamArea1.Sprites = Particle1;
	LaserBeamArea1.Anim.PushBack({ 48,264 - 10,4,8 + 21 });  //264
	LaserBeamArea1.Anim.PushBack({ 57,261 - 5,6,15 + 15 });  //261
	LaserBeamArea1.Anim.PushBack({ 66,254,11,31 });  //254
	LaserBeamArea1.Anim.loop = false;
	LaserBeamArea1.Anim.speed = 0.3f;
	LaserBeamArea1.Speed.x = 2;

	LaserBeamArea2.Sprites = Particle1;
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

	LaserBeamArea3.Sprites = Particle1;
	LaserBeamArea3.Anim.PushBack({ 66,254,47,31 });
	LaserBeamArea3.Anim.loop = false;
	LaserBeamArea3.Anim.speed = 0.1;
	LaserBeamArea3.Speed.x = 8;
	LaserBeamArea3.Life = 1000;

	int countExp_x= 0;
	int countExp_y = 0;
	
	for (int i = 0; i < 14; ++i) {
		EnemyExplosion.Anim.PushBack({ countExp_x, countExp_y, 32, 32 });
		countExp_x += 32;
		if (countExp_x >= 32*4) {
			countExp_y += 32;
			countExp_x = 0;
		}
	}
	EnemyExplosion.Anim.speed = 0.3f;
	EnemyExplosion.Anim.loop = false;
	EnemyExplosion.Sprites = Explosion_Texture;
	BossShoot.Life = 5300;
  
	//Boss
	BossShoot.Sprites = Particle3;
	BossShoot.Anim.PushBack({ 129,256, 63, 32 });
	BossShoot.Anim.PushBack({ 194,260, 63, 32 });
	BossShoot.Anim.loop = true;
	BossShoot.Life = 1300;
	BossShoot.Speed.x = -4;
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

	


	FogExplosion.Sprites = Particle5;
	FogExplosion.Anim.PushBack({29,0,14,16 });
	FogExplosion.Anim.PushBack({45,0,16,16});
	FogExplosion.Anim.PushBack({63,0,15,14});
	FogExplosion.Anim.PushBack({80,0,21,16 });
	FogExplosion.Anim.PushBack({103,0,21,24 });
	FogExplosion.Anim.PushBack({0,26,27,29});
	FogExplosion.Anim.PushBack({29,26,28,31  });
	FogExplosion.Anim.PushBack({61,26,30,32 });
	FogExplosion.Anim.PushBack({95,26,31,32});
	FogExplosion.Anim.PushBack({0,60,31,32});
	FogExplosion.Anim.PushBack({34,60,31,31 });
	FogExplosion.Anim.PushBack({67,74,31,16});
	FogExplosion.Anim.PushBack({0,94,31,16 });
	FogExplosion.Anim.PushBack({35,98,17,11});


	FogExplosion.Anim.loop = true;
	FogExplosion.Anim.speed = 0.3f;
	FogExplosion.Speed.y =1;

	HOU_Shot.Anim.PushBack({ 117,250,13,13 });
	MaleTears.Sprites = Particle3;
	MaleTears.Anim.PushBack({ 5,344,1,1});
	MaleTears.Anim.PushBack({ 14,344,2,1 });
	MaleTears.Anim.PushBack({ 23,344,3,2 }); 
	MaleTears.Anim.PushBack({ 33,343,4,3});
	MaleTears.Anim.PushBack({ 43,342,4,4 });
	MaleTears.Anim.PushBack({ 53,342,4,4 });
	MaleTears.Anim.PushBack({ 63,342,5,5});
	MaleTears.Anim.PushBack({ 72,342,6,5 });
	MaleTears.Anim.PushBack({ 82,342,6,5 });
	MaleTears.Anim.PushBack({ 92,341,6,6 });
	MaleTears.Anim.PushBack({ 102,341,7,6 });
	MaleTears.Anim.PushBack({ 111,341,8,7 });
	MaleTears.Anim.PushBack({ 120,340,9,9 });
	MaleTears.Anim.PushBack({ 130,339,10,10 });
	MaleTears.Anim.PushBack({ 2,350,9,12 });
	MaleTears.Anim.PushBack({ 15,350,11,13 });
	MaleTears.Anim.PushBack({ 29,350,11,12 });
	MaleTears.Anim.PushBack({ 43,350,13,13 });
	MaleTears.Anim.PushBack({ 56,349,14,12 });
	MaleTears.Anim.loop = false;
	MaleTears.Anim.speed = 0.3f;
	MaleTears.Speed.x = -1;
	MaleTears.Life = 5000;
	MaleTears.Speed.y = 2;
	//MaleTears.Speed.y = 0.01*((3*MaleTears.Position.x ^ 3)+2*(MaleTears.Position.x)+3);


	//HOU_Shot.Anim.PushBack({117,263,13,13});
	HOU_Shot.Anim.speed = 0.2f;
	HOU_Shot.Anim.loop = true;
	HOU_Shot.Sprites = Particle1;
	HOU_Shot.Life = 2200;
	HOU_Shot.Speed.x = 0;
	HOU_Shot.Speed.y = 0;
  
	BeeShot.Anim.PushBack({ 261,270,5,5 });
	BeeShot.Anim.PushBack({ 266,270,5,5 });
	BeeShot.Anim.PushBack({ 271,270,5,5 });
	BeeShot.Anim.PushBack({ 276,270,5,5 });
	BeeShot.Anim.loop = true;
	BeeShot.Life = 3000;
	BeeShot.Anim.speed = 0.2f;
	BeeShot.Sprites = Particle2;
	BeeShot.Speed.x = 0;
	BeeShot.Speed.y = 0;

	TankBigShoot.Anim.PushBack({ 286,266,13,13 });
	TankBigShoot.Anim.PushBack({ 299,266,13,13 });
	TankBigShoot.Anim.PushBack({ 312,266,13,13 });
	TankBigShoot.Anim.PushBack({ 325,266,13,13 });
	TankBigShoot.Anim.PushBack({ 338,266,13,13 });
	TankBigShoot.Anim.PushBack({ 351,266,13,13 });
	TankBigShoot.Anim.PushBack({ 364,266,13,13 });
	TankBigShoot.Anim.PushBack({ 377,266,13,13 });
	TankBigShoot.Life = 3000;
	TankBigShoot.Speed.x = 0;
	TankBigShoot.Speed.y = 0;
	TankBigShoot.Anim.loop = true;
	TankBigShoot.Anim.speed = 0.3;
	TankBigShoot.Sprites = Particle2;

  //HOU
	HOU_Shot_p2.Anim.PushBack({ 117,250,13,13 });
	HOU_Shot_p2.Anim.speed = 0.2f;
	HOU_Shot_p2.Anim.loop = true;
	HOU_Shot_p2.Sprites = Particle1;
	HOU_Shot_p2.Life = 2200;
	HOU_Shot_p2.Speed.x = 0;
	HOU_Shot_p2.Speed.y = 0;
	
	BeeShot.Anim.PushBack({261,270,5,5});
	BeeShot.Anim.PushBack({266,270,5,5});
	BeeShot.Anim.PushBack({271,270,5,5});
	BeeShot.Anim.PushBack({276,270,5,5});
	BeeShot.Anim.loop = true;
	BeeShot.Life = 3000;
	BeeShot.Anim.speed = 0.2f;
	BeeShot.Sprites = Particle2;
	BeeShot.Speed.x = 0;
	BeeShot.Speed.y= 0;

	Red_ThrowBall_pl1.Anim.PushBack({0,0,32,32});
	Red_ThrowBall_pl1.Anim.PushBack({ 32,0,32,32 });
	Red_ThrowBall_pl1.Anim.PushBack({ 64,0,32,32 });
	Red_ThrowBall_pl1.Anim.PushBack({ 96,0,32,32 });
	Red_ThrowBall_pl1.Anim.loop = true;

	Red_ThrowBall_pl1.Anim.speed = 0.2f;
	Red_ThrowBall_pl1.Sprites = Particle4;
	Red_ThrowBall_pl1.Speed.x = 0;
	Red_ThrowBall_pl1.Speed.x = 0;
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
	App->sound->UnloadChunks(ImpactExplosionSound2);

	App->textures->Unload(Particle1);
	App->textures->Unload(Particle2);
	App->textures->Unload(Particle3);
	App->textures->Unload(Particle4);
	App->textures->Unload(Particle5);
	App->textures->Unload(Particle6);
	App->textures->Unload(Explosion_Texture);
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
			if (collider_type != COLLIDER_NONE ) {
				p->collider = App->collision->AddCollider(p->Anim.GetCurrentFrame(), collider_type, this);
			}
			
			active[i] = p;
			break;
			
		}			
	}

	randomExplosionSound = rand() % 2 + 1;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//BOSS TANK LIFE HERE XDDDD
		if(c1->type == COLLIDER_PLAYER_SHOT)


		// DON'T DESTROY LASERBEAM WHEN COLLIDES
		
		if (active[i] != nullptr && active[i]->collider == c1 && (c1->type == COLLIDER_PLAYER_LASERBEAM_SHOT || c1->type == COLLIDER_PLAYER_LASERBEAM_SHOT2)) {

			if (c2->type == COLLIDER_ENEMY || c2->type == COLLIDER_WALL)
				//AddParticle(ImpactExplosion, active[i]->Position.x, active[i]->Position.y);
			if (c2->type == COLLIDER_ENEMY) {
				
				if (randomExplosionSound == 1) {
					Mix_PlayChannel(-1, ImpactExplosionSound, 0);
				}
				else if (randomExplosionSound == 2) {
					Mix_PlayChannel(-1, ImpactExplosionSound2, 0);
				}
				
				if (active[i]->TimesCollided == 0 ) {
					active[i]->TimesCollided = 1;
						
					//AÑADIR AQUI LA DESINTEGRACIÓN DE LAS AREAS DEL LASER CUANDO LOS SPRITES ESTÉN BIÉN (LASER AREA 2)
				}						
			
			}
			break;
		}
		// Always destroy particles that collide AND AREN`T LASSER BEAM
		if (active[i] != nullptr && active[i]->collider == c1 && (c1->type != COLLIDER_PLAYER_LASERBEAM_SHOT || c1->type != COLLIDER_PLAYER_LASERBEAM_SHOT2)) {
			
			if (c2->type == COLLIDER_ENEMY || c2->type == COLLIDER_WALL)
				//	AddParticle(ImpactExplosion,active[i]->Position.x, active[i]->Position.y);
			if (c2->type == COLLIDER_ENEMY) {
				
				if (randomExplosionSound == 1) {
					Mix_PlayChannel(-1, ImpactExplosionSound, 0);
				}
				else if (randomExplosionSound == 2) {
					Mix_PlayChannel(-1, ImpactExplosionSound2, 0);
				}
				
 					/*AddParticle(EnemyExplosion, active[i]->Position.x, active[i]->Position.y);
					AddParticle(EnemyExplosion, active[i]->Position.x + 3, active[i]->Position.y -2, COLLIDER_NONE, 200);
					AddParticle(EnemyExplosion, active[i]->Position.x - 3, active[i]->Position.y +2, COLLIDER_NONE, 200);*/
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