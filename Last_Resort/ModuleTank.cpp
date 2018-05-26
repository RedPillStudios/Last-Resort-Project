#include "ModuleTank.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleSceneLvl1.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "ModuleUI.h"


#include "SDL/include/SDL_timer.h"
#include "SDL/include/SDL.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
ModuleTank::ModuleTank() {

	//TANK ANIMS
	WaitingPos.PushBack({ 0,0,157,63 });
	WaitingPos.loop = true;
	WaitingPos.speed = 0.1;

	CorriendoAlTrote.PushBack({ 0,0,157,63 });
	CorriendoAlTrote.PushBack({ 0,63,157,63 });
	CorriendoAlTrote.PushBack({ 0,127,157,63 });
	CorriendoAlTrote.PushBack({ 0,127+64,157,63 });
	
	CorriendoAlTrote.loop = true;
	CorriendoAlTrote.speed = 0.1;
	//ENGINE ANIM
	LidoaTankEngine.PushBack({ 158,0,31,31 });
	LidoaTankEngine.PushBack({ 158,31,31,31 });
	LidoaTankEngine.PushBack({ 158,62,31,31 });
	LidoaTankEngine.PushBack({ 158,93,31,31 });
	LidoaTankEngine.PushBack({ 0,50,30,27 });
	LidoaTankEngine.PushBack({ 0,50,30,27 });
	LidoaTankEngine.PushBack({ 0,50,30,27 });
	LidoaTankEngine.PushBack({ 0,50,30,27 });
	LidoaTankEngine.PushBack({ 0,50,30,27 });
	LidoaTankEngine.PushBack({ 0,50,30,27 });
	LidoaTankEngine.PushBack({ 0,50,30,27 });

	LidoaTankEngine.loop = true;
	LidoaTankEngine.speed = 0.1;
	
	//TURRET ANIMS
	BigTurretPos1.PushBack({160,128,28,12});
	BigTurretPos1.loop = true;
	BigTurretPos2.PushBack({ 161,140,28,12 });
	BigTurretPos2.loop = true;
	BigTurretPos3.PushBack({ 161,152,28,14 });
	BigTurretPos3.loop = true;
	BigTurretPos4.PushBack({ 161,166,28,14 });
	BigTurretPos4.loop = true;
	BigTurretPos5.PushBack({ 161,181,28,13 });
	BigTurretPos5.loop = true;
	
	LittleTurretPos1.PushBack({166,197,15,6});
	LittleTurretPos1.loop = true;
	LittleTurretPos2.PushBack({167,204,13,8});
	LittleTurretPos2.loop = true;
	LittleTurretPos3.PushBack({167,212,13,9});
	LittleTurretPos3.loop = true;
	LittleTurretPos4.PushBack({167,221,13,9});
	LittleTurretPos4.loop = true;
	
	

	
}

ModuleTank::~ModuleTank() {}

bool ModuleTank::Start() {
	//Spawn pos
	TankPosition = { (3000.0), 157.0 };
	//anim declarated
	CorriendoAlTroteAnim = &CorriendoAlTrote;
	WaitingPosAnim = &WaitingPos;
	LidoaTankEngineAnim = &LidoaTankEngine;
	BigTurretPos1Anim = &BigTurretPos1;
	BigTurretPos2Anim = &BigTurretPos2;
	BigTurretPos3Anim = &BigTurretPos3;
	BigTurretPos4Anim = &BigTurretPos4;
	BigTurretPos5Anim = &BigTurretPos5;
	LittleTurretPos1Anim = &LittleTurretPos1;
	LittleTurretPos2Anim = &LittleTurretPos2;
	LittleTurretPos3Anim = &LittleTurretPos3;
	LittleTurretPos4Anim = &LittleTurretPos4;
	
	//TankCollider1 = App->collision->AddCollider({ 200,60,50,50 }, COLLIDER_ENEMY); done to test

	TankCollider1 = App->collision->AddCollider({ (int)TankPosition.x,(int)TankPosition.y,50,20 },  COLLIDER_ENEMY, this); 
	TankCollider2 = App->collision->AddCollider({ (int)TankPosition.x,(int)TankPosition.y,120,15 }, COLLIDER_ENEMY, this);
	TankCollider3 = App->collision->AddCollider({ (int)TankPosition.x,(int)TankPosition.y,100,20 }, COLLIDER_ENEMY, this);
	TankCollider4 = App->collision->AddCollider({ (int)TankPosition.x,(int)TankPosition.y,100,20 }, COLLIDER_ENEMY, this);
	TankCollider5 = App->collision->AddCollider({ (int)TankPosition.x,(int)TankPosition.y,20,20 }, COLLIDER_ENEMY, this);

	//load textures
	BossTank = App->textures->Load("Images/Bosses/Tank_Stage1_Sprite.png");
	//colliders
	life = 50;
	
	return true;
}

bool ModuleTank::CleanUp() {

	//VAMO A ASEGURARNO Q NO AI MEMORILIKS
	App->textures->Unload(BossTank);

	TankCollider1->to_delete = true;
	TankCollider2->to_delete = true;
	TankCollider3->to_delete = true;
	TankCollider4->to_delete = true;
	TankCollider5->to_delete = true;

	CleanUpDone = true;
	return true;
}

update_status ModuleTank::Update() {



	TimerShoot++;
	TimerShoot2++;

	TankCollider1->SetPos((int)TankPosition.x + 50, (int)TankPosition.y + Trote);
	TankCollider2->SetPos((int)TankPosition.x + 3 , (int)TankPosition.y + 22 + Trote);
	TankCollider3->SetPos((int)TankPosition.x + 33, (int)TankPosition.y + 30 + Trote);
	TankCollider4->SetPos((int)TankPosition.x + 40, (int)TankPosition.y + 45 + Trote);
	TankCollider5->SetPos((int)TankPosition.x + 37, (int)TankPosition.y + 7 + Trote);

	if (App->player->Dead == false) {
		PlayerPos = App->player->position;
	}
	else if (App->player->Dead == true) {
		PlayerPos = App->player2->positionp2;
	}

	
	
	Radiants1 = atan2(PlayerPos.y + 3 - TankPosition.y - 3, PlayerPos.x + 10 - TankPosition.x - 50); //BIG SHOOT
	
	//Radiants2 = atan2(PlayerPos.y - TankPosition.y - 3, PlayerPos.x - TankPosition.x + 47);
	Angle1 = Radiants1 * (180 / PI);
	

	
	if (Radiants1 < 0) {
		Angle1 += 360; // quan rad es negatiu li donem la volta sumant 360*
	}
	

	//MOVEMENT CONTROL OF THE TANK
	
	if (!ReachPos1 && !ReachPos2 ) {
		TankPosition.x += 0.5;
		App->render->Blit(BossTank, TankPosition.x , TankPosition.y + Trote, &WaitingPosAnim->GetCurrentFrame()); // tanque
		if (!DestroyTurret) {
			App->render->Blit(BossTank, TankPosition.x + 47, TankPosition.y - 3 + Trote, &BigTurretPos1Anim->GetCurrentFrame()); // torreta grande
		}
		App->render->Blit(BossTank, TankPosition.x + 83, TankPosition.y + 3 + Trote, &LittleTurretPos1Anim->GetCurrentFrame()); // torreta pequeña
		if (TankPosition.x <= App->scene1background->position_min_limit + 100) {
			//App->render->Blit(BossTank, Position.x + 13, Position.y + 22 + Trote, &LidoaTankEngineAnim->GetCurrentFrame());
		}
	}
	
	if (TankPosition.x <= App->scene1background->position_min_limit + 20 && !LimitReached ) {
		ReachPos1 = true;
	}
	if (TankPosition.x > 3600) {
		LimitReached = true;
	}
	if (ReachPos1) {
		TankPosition.x += 1.5;
		if (TroteDelay < SDL_GetTicks() - 60) {
					Trote = Trote * -1;	
					TroteDelay = SDL_GetTicks();
				}
		App->render->Blit(BossTank, TankPosition.x, TankPosition.y + Trote, &CorriendoAlTroteAnim->GetCurrentFrame());
		if (TankPosition.x <= App->scene1background->position_min_limit + 200) {
			App->render->Blit(BossTank, TankPosition.x + 13, TankPosition.y + 22 + Trote, &LidoaTankEngineAnim->GetCurrentFrame());
		}
		if (TankPosition.x + 157 >= App->scene1background->position_max_limit - 2) {
			ReachPos2 = true;
			ReachPos1 = false;
		}
	}
	if (ReachPos2) {
		TankPosition.x += 1;
		if (TroteDelay < SDL_GetTicks() - 60) {
			Trote = Trote * -1;
			TroteDelay = SDL_GetTicks();
		}
		App->render->Blit(BossTank, TankPosition.x, TankPosition.y + Trote, &CorriendoAlTroteAnim->GetCurrentFrame());
	}
	if (LimitReached) {
		ReachPos2 = false;
		if (TroteDelay < SDL_GetTicks() - 60) {
			Trote = Trote * -1;
			TroteDelay = SDL_GetTicks();
		}
	}
	

	//TORRET // LittleTurretPos1Anim

	P1Posx = App->player->position.x;
	P2Posx = App->player2->positionp2.x;
	P1Posy = App->player->position.y;
	P2Posy = App->player2->positionp2.y;
	
	
		if (((P1Posx - TankPosition.x) + (P1Posy - TankPosition.y)) > ((P2Posx - TankPosition.x) + (P2Posy - TankPosition.y))) {
			
				if (App->player->position.x <= TankPosition.x && App->player->position.y >= TankPosition.y - 30) {
					if (P2Posy > TankPosition.y ) { AngleNotValid = true; }
					if (!DestroyTurret) {
						App->render->Blit(BossTank, TankPosition.x + 47, TankPosition.y - 3 + Trote, &BigTurretPos1Anim->GetCurrentFrame());// Big TurretAnim
					}
					App->render->Blit(BossTank, TankPosition.x + 83, TankPosition.y + 3 + Trote, &LittleTurretPos1Anim->GetCurrentFrame());// LittleTurretAnim
				}
				else if (App->player->position.x <= TankPosition.x && App->player->position.y <= TankPosition.y) {
					AngleNotValid = false;
					if (!DestroyTurret) {
						App->render->Blit(BossTank, TankPosition.x + 49, TankPosition.y - 5 + Trote, &BigTurretPos2Anim->GetCurrentFrame());// Big TurretAnim
					}
					App->render->Blit(BossTank, TankPosition.x + 85, TankPosition.y + 1 + Trote, &LittleTurretPos2Anim->GetCurrentFrame());// LittleTurretAnim
				}
				else if (App->player->position.x >= TankPosition.x && App->player->position.x <= TankPosition.x + 50 && App->player->position.y <= TankPosition.y) {
					AngleNotValid = false;
					if (!DestroyTurret) {
						App->render->Blit(BossTank, TankPosition.x + 49, TankPosition.y - 7 + Trote, &BigTurretPos3Anim->GetCurrentFrame());// Big TurretAnim
					}
					App->render->Blit(BossTank, TankPosition.x + 85, TankPosition.y + Trote, &LittleTurretPos3Anim->GetCurrentFrame());// LittleTurretAnim
				}
				else if (App->player->position.x >= TankPosition.x + 50 && App->player->position.x <= TankPosition.x + 100 && App->player->position.y <= TankPosition.y) {
					AngleNotValid = false;
					if (!DestroyTurret) {
						App->render->Blit(BossTank, TankPosition.x + 49, TankPosition.y - 7 + Trote, &BigTurretPos4Anim->GetCurrentFrame());// Big TurretAnim
					}
					App->render->Blit(BossTank, TankPosition.x + 85, TankPosition.y + Trote, &LittleTurretPos4Anim->GetCurrentFrame());// LittleTurretAnim
				}
				else if (App->player->position.x >= TankPosition.x + 100 && App->player->position.y <= TankPosition.y) {
					AngleNotValid = false;
					if (!DestroyTurret) {
						App->render->Blit(BossTank, TankPosition.x + 49, TankPosition.y - 6 + Trote, &BigTurretPos5Anim->GetCurrentFrame());// Big TurretAnim
					}
					App->render->Blit(BossTank, TankPosition.x + 85, TankPosition.y + Trote, &LittleTurretPos4Anim->GetCurrentFrame());// LittleTurretAnim
				}
			
		}
		else if (((P1Posx - TankPosition.x) + (P1Posy - TankPosition.y)) < ((P2Posx - TankPosition.x) + (P2Posy - TankPosition.y))) {
			
				if (App->player2->positionp2.x <= TankPosition.x && App->player2->positionp2.y >= TankPosition.y-30) {
					if (!DestroyTurret) {
						App->render->Blit(BossTank, TankPosition.x + 47, TankPosition.y - 3 + Trote, &BigTurretPos1Anim->GetCurrentFrame());// Big TurretAnim
					}
					App->render->Blit(BossTank, TankPosition.x + 83, TankPosition.y + 3 + Trote, &LittleTurretPos1Anim->GetCurrentFrame());// LittleTurretAnim
					if(P1Posy > TankPosition.y){ AngleNotValid = true; }
					
				}
				else if (App->player2->positionp2.x <= TankPosition.x && App->player2->positionp2.y <= TankPosition.y) {
					AngleNotValid = false;
					if (!DestroyTurret) {
						App->render->Blit(BossTank, TankPosition.x + 49, TankPosition.y - 5 + Trote, &BigTurretPos2Anim->GetCurrentFrame());// Big TurretAnim
					}
					App->render->Blit(BossTank, TankPosition.x + 85, TankPosition.y + 1 + Trote, &LittleTurretPos2Anim->GetCurrentFrame());// LittleTurretAnim
				}
				else if (App->player2->positionp2.x >= TankPosition.x && App->player2->positionp2.x <= TankPosition.x + 50 && App->player2->positionp2.y <= TankPosition.y) {
					AngleNotValid = false;
					if (!DestroyTurret) {
						App->render->Blit(BossTank, TankPosition.x + 49, TankPosition.y - 7 + Trote, &BigTurretPos3Anim->GetCurrentFrame());// Big TurretAnim
					}
					App->render->Blit(BossTank, TankPosition.x + 85, TankPosition.y + Trote, &LittleTurretPos3Anim->GetCurrentFrame());// LittleTurretAnim
				}
				else if (App->player2->positionp2.x >= TankPosition.x + 50 && App->player2->positionp2.x <= TankPosition.x + 100 && App->player2->positionp2.y <= TankPosition.y) {
					AngleNotValid = false;
					if (!DestroyTurret) {
						App->render->Blit(BossTank, TankPosition.x + 49, TankPosition.y - 7 + Trote, &BigTurretPos4Anim->GetCurrentFrame());// Big TurretAnim
					}
					App->render->Blit(BossTank, TankPosition.x + 85, TankPosition.y + Trote, &LittleTurretPos4Anim->GetCurrentFrame());// LittleTurretAnim
				}
				else if (App->player2->positionp2.x >= TankPosition.x + 100 && App->player2->positionp2.y <= TankPosition.y) {
					AngleNotValid = false;
					if (!DestroyTurret) {
						App->render->Blit(BossTank, TankPosition.x + 49, TankPosition.y - 6 + Trote, &BigTurretPos5Anim->GetCurrentFrame());// Big TurretAnim
					}
					App->render->Blit(BossTank, TankPosition.x + 85, TankPosition.y + Trote, &LittleTurretPos4Anim->GetCurrentFrame());// LittleTurretAnim
				}
			
		}
	
		// TURRET SHOOT
		
		if ((ReachPos1 || ReachPos2) && !LimitReached && !AngleNotValid) {
			if(!DestroyTurret){
				if (TimerShoot >= 75) {
					App->particles->TankBigShoot.Speed.x = 3 * (cos(Angle1*PI / 180));
					//App->particles->TankBigShoot.Speed.x = 0.05 * ((PlayerPos.y + 3 - TankPosition.y - 3)/ tan(Angle1 * PI / 180.0));// x=y/tan of angle1
					App->particles->TankBigShoot.Speed.x++;
					App->particles->TankBigShoot.Speed.y = 3 * (sin(Angle1*PI / 180));
					//App->particles->TankBigShoot.Speed.y = 0.05 * ((PlayerPos.x + 10 - TankPosition.x + 50) * tan(Angle1 * PI / 180.0)); // y = tang of angle 1 * x
					App->particles->AddParticle(App->particles->TankBigShoot, TankPosition.x + 55, TankPosition.y - 12, COLLIDER_ENEMY_SHOT);
					TimerShoot = 0;
				}
			}
		    if (TimerShoot2 >= 75) {
				App->particles->BeeShot.Speed.x = 3 * (cos(Angle1*PI / 180));
				//App->particles->BeeShot.Speed.x = 0.05 * ((PlayerPos.y + 3 - TankPosition.y - 3) / tan(Angle1 * PI / 180.0));// x=y/tan of angle1
				App->particles->BeeShot.Speed.x++;
				App->particles->BeeShot.Speed.y = 3 * (sin(Angle1*PI / 180));
				//App->particles->BeeShot.Speed.y = 0.05 * ((PlayerPos.x + 10 - TankPosition.x + 50) * tan(Angle1 * PI / 180.0));
				App->particles->AddParticle(App->particles->BeeShot, TankPosition.x + 86, TankPosition.y -3, COLLIDER_ENEMY_SHOT);
				TimerShoot2 = 0;
			}
		}
		if (DestroyTurret && count <100) {
			if (count == 20 || count == 35 || count == 50 || count == 65) {
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 45, (int)TankPosition.y - 5);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 50, (int)TankPosition.y + 1);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 56, (int)TankPosition.y - 10);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 40, (int)TankPosition.y + -8);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 60, (int)TankPosition.y + -4);
			}
			count++;
		}
		if (Dead && count2 < 100) {
 			if (count2 == 10 || count2 == 30 ||  count2 == 50 || count2 == 80) {
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 20, (int)TankPosition.y);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x, (int)TankPosition.y + 28);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 10, (int)TankPosition.y);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x, (int)TankPosition.y + 44);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 30, (int)TankPosition.y);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x, (int)TankPosition.y + 5);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 40, (int)TankPosition.y + 44);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 35, (int)TankPosition.y + 23);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x, (int)TankPosition.y + 15);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 15, (int)TankPosition.y);

				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 33, (int)TankPosition.y + 22);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 21, (int)TankPosition.y - 28);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 55, (int)TankPosition.y - 3);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x, (int)TankPosition.y - 44);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 66, (int)TankPosition.y);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x, (int)TankPosition.y + 5);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 40, (int)TankPosition.y + 44);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 35, (int)TankPosition.y - 23);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x, (int)TankPosition.y + 40);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 70, (int)TankPosition.y - 30);

				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 69, (int)TankPosition.y + 22);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 90, (int)TankPosition.y - 28);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 80, (int)TankPosition.y - 3);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 97, (int)TankPosition.y - 44);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 110, (int)TankPosition.y);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x, (int)TankPosition.y + 5);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 120, (int)TankPosition.y + 44);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 105, (int)TankPosition.y - 23);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x, (int)TankPosition.y + 40);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 85, (int)TankPosition.y - 30);
			}
			else if (count2 == 20 || count2 == 40 || count2 == 60 || count2 == 70 || count2 == 90) {
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x +50, (int)TankPosition.y);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x, (int)TankPosition.y + -2);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + -14, (int)TankPosition.y);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x, (int)TankPosition.y + 33);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x +22, (int)TankPosition.y);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x, (int)TankPosition.y + 5);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 44, (int)TankPosition.y + -2);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 43, (int)TankPosition.y + 33);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x, (int)TankPosition.y + 15);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 1, (int)TankPosition.y-10);

				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 33+4, (int)TankPosition.y + 22+5);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 21-10, (int)TankPosition.y - 28-15);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 55-15, (int)TankPosition.y - 3);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x, (int)TankPosition.y - 44+20);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 66+7, (int)TankPosition.y);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x, (int)TankPosition.y + 5+5);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 40-5, (int)TankPosition.y + 44-12);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 35-12, (int)TankPosition.y - 23+3);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x+30, (int)TankPosition.y + 40-8);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 70+12, (int)TankPosition.y - 30+12);

				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 90, (int)TankPosition.y + 12);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 69, (int)TankPosition.y - 58);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 97, (int)TankPosition.y - 2);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 80, (int)TankPosition.y - 54);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x +120, (int)TankPosition.y);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x, (int)TankPosition.y +12);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 110, (int)TankPosition.y + 24);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x + 98, (int)TankPosition.y - 33);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x, (int)TankPosition.y + 30);
				App->particles->AddParticle(App->particles->EnemyExplosion, (int)TankPosition.x +81, (int)TankPosition.y - 44);
			}
			count2++;
		}
		if (count2 > 95) {
			DestroyTank = true;
		}
	
	return UPDATE_CONTINUE;
}

void ModuleTank::OnCollision(Collider *c1, Collider *c2) {

	if ((c1->type == COLLIDER_PLAYER_SHOT || c2->type == COLLIDER_PLAYER_SHOT )) {

		--BossLife;
		LOG("BOSS LIFE    - 1");
		if (BossLife < 25 && count == 0) {
			DestroyTurret = true;
		}
		if (BossLife <= 0 && count2 ==0) {
			App->fonts->ScoreP1 += 2000;
			App->fonts->ScoreP2 += 2000;
			Dead = true;
		}
	}
}