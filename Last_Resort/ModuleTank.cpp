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
	TankPosition = { (200.0), 157.0 };
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
	
		
	//load textures
	BossTank = App->textures->Load("Images/Bosses/Tank_Stage1_Sprite.png");
	//colliders
	life = 50;
	//Asigments
	TimeOnMovement = 0;
	return true;
}

bool ModuleTank::CleanUp() {

	//VAMO A ASEGURARNO Q NO AI MEMORILIKS
	return true;
}

update_status ModuleTank::Update() {

	TimerShoot++;
	TimerShoot2++;

	PlayerPos = App->player->position;
	
	Radiants1 = atan2( PlayerPos.y + 3 - TankPosition.y - 3 , PlayerPos.x + 10 - TankPosition.x + 50 ); //BIG SHOOT
	
	//Radiants2 = atan2(PlayerPos.y - TankPosition.y - 3, PlayerPos.x - TankPosition.x + 47);
	Angle1 = Radiants1 * (180 / PI);
	

	
	if (Radiants1 < 0) {
		Angle1 += 360; // quan rad es negatiu li donem la volta sumant 360*
	}
	

	//MOVEMENT CONTROL OF THE TANK
	
	if (!ReachPos1 && !ReachPos2 ) {
		TankPosition.x += 0.5;
		App->render->Blit(BossTank, TankPosition.x , TankPosition.y + Trote, &WaitingPosAnim->GetCurrentFrame()); // tanque
		App->render->Blit(BossTank, TankPosition.x + 47, TankPosition.y -3 + Trote, &BigTurretPos1Anim->GetCurrentFrame()); // torreta grande
		App->render->Blit(BossTank, TankPosition.x + 83, TankPosition.y + 3 + Trote, &LittleTurretPos1Anim->GetCurrentFrame()); // torreta pequeña
		if (TankPosition.x <= App->scene1background->position_min_limit + 100) {
			//App->render->Blit(BossTank, Position.x + 13, Position.y + 22 + Trote, &LidoaTankEngineAnim->GetCurrentFrame());
		}
	}
	
	if (TankPosition.x <= App->scene1background->position_min_limit + 20 && !LimitReached ) {
		ReachPos1 = true;
	}
	if (TankPosition.x > 10000) {
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
			if (ReachPos2 || ReachPos1) {
				if (App->player->position.x <= TankPosition.x && App->player->position.y >= TankPosition.y) {
					AngleNotValid = true;
					App->render->Blit(BossTank, TankPosition.x + 47, TankPosition.y - 3 + Trote, &BigTurretPos1Anim->GetCurrentFrame());// Big TurretAnim
					App->render->Blit(BossTank, TankPosition.x + 83, TankPosition.y + 3 + Trote, &LittleTurretPos1Anim->GetCurrentFrame());// LittleTurretAnim
				}
				else if (App->player->position.x <= TankPosition.x && App->player->position.y <= TankPosition.y) {
					AngleNotValid = false;
					App->render->Blit(BossTank, TankPosition.x + 49, TankPosition.y - 5 + Trote, &BigTurretPos2Anim->GetCurrentFrame());// Big TurretAnim
					App->render->Blit(BossTank, TankPosition.x + 85, TankPosition.y + 1 + Trote, &LittleTurretPos2Anim->GetCurrentFrame());// LittleTurretAnim
				}
				else if (App->player->position.x >= TankPosition.x && App->player->position.x <= TankPosition.x + 50 && App->player->position.y <= TankPosition.y) {
					AngleNotValid = false;
					App->render->Blit(BossTank, TankPosition.x + 49, TankPosition.y - 7 + Trote, &BigTurretPos3Anim->GetCurrentFrame());// Big TurretAnim
					App->render->Blit(BossTank, TankPosition.x + 85, TankPosition.y + Trote, &LittleTurretPos3Anim->GetCurrentFrame());// LittleTurretAnim
				}
				else if (App->player->position.x >= TankPosition.x + 50 && App->player->position.x <= TankPosition.x + 100 && App->player->position.y <= TankPosition.y) {
					AngleNotValid = false;
					App->render->Blit(BossTank, TankPosition.x + 49, TankPosition.y - 7 + Trote, &BigTurretPos4Anim->GetCurrentFrame());// Big TurretAnim
					App->render->Blit(BossTank, TankPosition.x + 85, TankPosition.y + Trote, &LittleTurretPos4Anim->GetCurrentFrame());// LittleTurretAnim
				}
				else if (App->player->position.x >= TankPosition.x + 100 && App->player->position.y <= TankPosition.y) {
					AngleNotValid = false;
					App->render->Blit(BossTank, TankPosition.x + 49, TankPosition.y - 6 + Trote, &BigTurretPos5Anim->GetCurrentFrame());// Big TurretAnim
					App->render->Blit(BossTank, TankPosition.x + 85, TankPosition.y + Trote, &LittleTurretPos4Anim->GetCurrentFrame());// LittleTurretAnim
				}
			}
		}
		else if (((P1Posx - TankPosition.x) + (P1Posy - TankPosition.y)) < ((P2Posx - TankPosition.x) + (P2Posy - TankPosition.y))) {
			if (ReachPos2 || ReachPos1) {
				if (App->player2->positionp2.x <= TankPosition.x && App->player2->positionp2.y >= TankPosition.y) {
					App->render->Blit(BossTank, TankPosition.x + 47, TankPosition.y - 3 + Trote, &BigTurretPos1Anim->GetCurrentFrame());// Big TurretAnim
					App->render->Blit(BossTank, TankPosition.x + 83, TankPosition.y + 3 + Trote, &LittleTurretPos1Anim->GetCurrentFrame());// LittleTurretAnim
					AngleNotValid = true;
				}
				else if (App->player2->positionp2.x <= TankPosition.x && App->player2->positionp2.y <= TankPosition.y) {
					AngleNotValid = false;
					App->render->Blit(BossTank, TankPosition.x + 49, TankPosition.y - 5 + Trote, &BigTurretPos2Anim->GetCurrentFrame());// Big TurretAnim
					App->render->Blit(BossTank, TankPosition.x + 85, TankPosition.y + 1 + Trote, &LittleTurretPos2Anim->GetCurrentFrame());// LittleTurretAnim
				}
				else if (App->player2->positionp2.x >= TankPosition.x && App->player2->positionp2.x <= TankPosition.x + 50 && App->player2->positionp2.y <= TankPosition.y) {
					AngleNotValid = false;
					App->render->Blit(BossTank, TankPosition.x + 49, TankPosition.y - 7 + Trote, &BigTurretPos3Anim->GetCurrentFrame());// Big TurretAnim
					App->render->Blit(BossTank, TankPosition.x + 85, TankPosition.y + Trote, &LittleTurretPos3Anim->GetCurrentFrame());// LittleTurretAnim
				}
				else if (App->player2->positionp2.x >= TankPosition.x + 50 && App->player2->positionp2.x <= TankPosition.x + 100 && App->player2->positionp2.y <= TankPosition.y) {
					AngleNotValid = false;
					App->render->Blit(BossTank, TankPosition.x + 49, TankPosition.y - 7 + Trote, &BigTurretPos4Anim->GetCurrentFrame());// Big TurretAnim
					App->render->Blit(BossTank, TankPosition.x + 85, TankPosition.y + Trote, &LittleTurretPos4Anim->GetCurrentFrame());// LittleTurretAnim
				}
				else if (App->player2->positionp2.x >= TankPosition.x + 100 && App->player2->positionp2.y <= TankPosition.y) {
					AngleNotValid = false;
					App->render->Blit(BossTank, TankPosition.x + 49, TankPosition.y - 6 + Trote, &BigTurretPos5Anim->GetCurrentFrame());// Big TurretAnim
					App->render->Blit(BossTank, TankPosition.x + 85, TankPosition.y + Trote, &LittleTurretPos4Anim->GetCurrentFrame());// LittleTurretAnim
				}
			}
		}
	
		// TURRET SHOOT
		if ((ReachPos1 || ReachPos2) && !LimitReached && !AngleNotValid) {
			if (TimerShoot >= 75) {
				App->particles->TankBigShoot.Speed.x = 3 * (cos(Angle1*PI / 180));
				App->particles->TankBigShoot.Speed.x++;
				App->particles->TankBigShoot.Speed.y = 3 * (sin(Angle1*PI / 180));
				App->particles->AddParticle(App->particles->TankBigShoot, TankPosition.x + 50, TankPosition.y - 20, COLLIDER_ENEMY_SHOT);
				TimerShoot = 0;
			}
		    if (TimerShoot2 >= 35) {
				App->particles->BeeShot.Speed.x = 3 * (cos(Angle1*PI / 180));
				App->particles->BeeShot.Speed.x++;
				App->particles->BeeShot.Speed.y = 3 * (sin(Angle1*PI / 180));
				App->particles->AddParticle(App->particles->BeeShot, TankPosition.x + 85, TankPosition.y - 20 , COLLIDER_ENEMY_SHOT);
				TimerShoot2 = 0;
			}
		}
		
		
	
	return UPDATE_CONTINUE;
}

update_status ModuleTank::PostUpdate() {

	return UPDATE_CONTINUE;
}
//void ModuleTank::OnCollision(Collider *c1, Collider *c2) {
//
//}
//
//void ModuleTank::Shooting() {
//
//}
//
//void ModuleTank::Charge() {
//
//	
//}
//TimerShoot++;
//TimerShoot2++;
//
//PlayerPos = App->player->position;
//Radiants1 = atan2(PlayerPos.y - TankPosition.y - 3, (PlayerPos.x - 30) - TankPosition.x + 50);
////Radiants2 = atan2(PlayerPos.y - TankPosition.y - 3, PlayerPos.x - TankPosition.x + 47);
//Angle1 = Radiants1 * (180 / PI);
//
//if (Radiants1 < 0) {
//	Angle1 += 360; // quan rad es negatiu li donem la volta sumant 360*
//}
//
//
////MOVEMENT CONTROL OF THE TANK
//
//if (!ReachPos1 && !ReachPos2) {
//	TankPosition.x += 0.5;
//	App->render->Blit(BossTank, TankPosition.x, TankPosition.y + Trote, &WaitingPosAnim->GetCurrentFrame()); // tanque
//	App->render->Blit(BossTank, TankPosition.x + 47, TankPosition.y - 3 + Trote, &BigTurretPos1Anim->GetCurrentFrame()); // torreta grande
//	App->render->Blit(BossTank, TankPosition.x + 83, TankPosition.y + 3 + Trote, &LittleTurretPos1Anim->GetCurrentFrame()); // torreta pequeña
//	if (TankPosition.x <= App->scene1background->position_min_limit + 100) {
//		//App->render->Blit(BossTank, Position.x + 13, Position.y + 22 + Trote, &LidoaTankEngineAnim->GetCurrentFrame());
//	}
//}
//
//if (TankPosition.x <= App->scene1background->position_min_limit + 20 && !LimitReached) {
//	ReachPos1 = true;
//}
//if (TankPosition.x > 10000) {
//	LimitReached = true;
//}
//if (ReachPos1) {
//	TankPosition.x += 1.5;
//	if (TroteDelay < SDL_GetTicks() - 60) {
//		Trote = Trote * -1;
//		TroteDelay = SDL_GetTicks();
//	}
//	App->render->Blit(BossTank, TankPosition.x, TankPosition.y + Trote, &CorriendoAlTroteAnim->GetCurrentFrame());
//	if (TankPosition.x <= App->scene1background->position_min_limit + 200) {
//		App->render->Blit(BossTank, TankPosition.x + 13, TankPosition.y + 22 + Trote, &LidoaTankEngineAnim->GetCurrentFrame());
//	}
//	if (TankPosition.x + 157 >= App->scene1background->position_max_limit - 2) {
//		ReachPos2 = true;
//		ReachPos1 = false;
//	}
//}
//if (ReachPos2) {
//	TankPosition.x += 1;
//	if (TroteDelay < SDL_GetTicks() - 60) {
//		Trote = Trote * -1;
//		TroteDelay = SDL_GetTicks();
//	}
//	App->render->Blit(BossTank, TankPosition.x, TankPosition.y + Trote, &CorriendoAlTroteAnim->GetCurrentFrame());
//}
//if (LimitReached) {
//	ReachPos2 = false;
//	if (TroteDelay < SDL_GetTicks() - 60) {
//		Trote = Trote * -1;
//		TroteDelay = SDL_GetTicks();
//	}
//}
//
//
////TORRET // LittleTurretPos1Anim
//
//P1Posx = App->player->position.x;
//P2Posx = App->player2->positionp2.x;
//P1Posy = App->player->position.y;
//P2Posy = App->player2->positionp2.y;
//
//
//if (((P1Posx - TankPosition.x) + (P1Posy - TankPosition.y)) > ((P2Posx - TankPosition.x) + (P2Posy - TankPosition.y))) {
//	if (ReachPos2 || ReachPos1) {
//		if (App->player->position.x <= TankPosition.x && App->player->position.y >= TankPosition.y) {
//			AngleNotValid = true;
//			App->render->Blit(BossTank, TankPosition.x + 47, TankPosition.y - 3 + Trote, &BigTurretPos1Anim->GetCurrentFrame());// Big TurretAnim
//			App->render->Blit(BossTank, TankPosition.x + 83, TankPosition.y + 3 + Trote, &LittleTurretPos1Anim->GetCurrentFrame());// LittleTurretAnim
//		}
//		else if (App->player->position.x <= TankPosition.x && App->player->position.y <= TankPosition.y) {
//			AngleNotValid = false;
//			App->render->Blit(BossTank, TankPosition.x + 49, TankPosition.y - 5 + Trote, &BigTurretPos2Anim->GetCurrentFrame());// Big TurretAnim
//			App->render->Blit(BossTank, TankPosition.x + 85, TankPosition.y + 1 + Trote, &LittleTurretPos2Anim->GetCurrentFrame());// LittleTurretAnim
//		}
//		else if (App->player->position.x >= TankPosition.x && App->player->position.x <= TankPosition.x + 50 && App->player->position.y <= TankPosition.y) {
//			AngleNotValid = false;
//			App->render->Blit(BossTank, TankPosition.x + 49, TankPosition.y - 7 + Trote, &BigTurretPos3Anim->GetCurrentFrame());// Big TurretAnim
//			App->render->Blit(BossTank, TankPosition.x + 85, TankPosition.y + Trote, &LittleTurretPos3Anim->GetCurrentFrame());// LittleTurretAnim
//		}
//		else if (App->player->position.x >= TankPosition.x + 50 && App->player->position.x <= TankPosition.x + 100 && App->player->position.y <= TankPosition.y) {
//			AngleNotValid = false;
//			App->render->Blit(BossTank, TankPosition.x + 49, TankPosition.y - 7 + Trote, &BigTurretPos4Anim->GetCurrentFrame());// Big TurretAnim
//			App->render->Blit(BossTank, TankPosition.x + 85, TankPosition.y + Trote, &LittleTurretPos4Anim->GetCurrentFrame());// LittleTurretAnim
//		}
//		else if (App->player->position.x >= TankPosition.x + 100 && App->player->position.y <= TankPosition.y) {
//			AngleNotValid = false;
//			App->render->Blit(BossTank, TankPosition.x + 49, TankPosition.y - 6 + Trote, &BigTurretPos5Anim->GetCurrentFrame());// Big TurretAnim
//			App->render->Blit(BossTank, TankPosition.x + 85, TankPosition.y + Trote, &LittleTurretPos4Anim->GetCurrentFrame());// LittleTurretAnim
//		}
//	}
//}
//else if (((P1Posx - TankPosition.x) + (P1Posy - TankPosition.y)) < ((P2Posx - TankPosition.x) + (P2Posy - TankPosition.y))) {
//	if (ReachPos2 || ReachPos1) {
//		if (App->player2->positionp2.x <= TankPosition.x && App->player2->positionp2.y >= TankPosition.y) {
//			App->render->Blit(BossTank, TankPosition.x + 47, TankPosition.y - 3 + Trote, &BigTurretPos1Anim->GetCurrentFrame());// Big TurretAnim
//			App->render->Blit(BossTank, TankPosition.x + 83, TankPosition.y + 3 + Trote, &LittleTurretPos1Anim->GetCurrentFrame());// LittleTurretAnim
//			AngleNotValid = true;
//		}
//		else if (App->player2->positionp2.x <= TankPosition.x && App->player2->positionp2.y <= TankPosition.y) {
//			AngleNotValid = false;
//			App->render->Blit(BossTank, TankPosition.x + 49, TankPosition.y - 5 + Trote, &BigTurretPos2Anim->GetCurrentFrame());// Big TurretAnim
//			App->render->Blit(BossTank, TankPosition.x + 85, TankPosition.y + 1 + Trote, &LittleTurretPos2Anim->GetCurrentFrame());// LittleTurretAnim
//		}
//		else if (App->player2->positionp2.x >= TankPosition.x && App->player2->positionp2.x <= TankPosition.x + 50 && App->player2->positionp2.y <= TankPosition.y) {
//			AngleNotValid = false;
//			App->render->Blit(BossTank, TankPosition.x + 49, TankPosition.y - 7 + Trote, &BigTurretPos3Anim->GetCurrentFrame());// Big TurretAnim
//			App->render->Blit(BossTank, TankPosition.x + 85, TankPosition.y + Trote, &LittleTurretPos3Anim->GetCurrentFrame());// LittleTurretAnim
//		}
//		else if (App->player2->positionp2.x >= TankPosition.x + 50 && App->player2->positionp2.x <= TankPosition.x + 100 && App->player2->positionp2.y <= TankPosition.y) {
//			AngleNotValid = false;
//			App->render->Blit(BossTank, TankPosition.x + 49, TankPosition.y - 7 + Trote, &BigTurretPos4Anim->GetCurrentFrame());// Big TurretAnim
//			App->render->Blit(BossTank, TankPosition.x + 85, TankPosition.y + Trote, &LittleTurretPos4Anim->GetCurrentFrame());// LittleTurretAnim
//		}
//		else if (App->player2->positionp2.x >= TankPosition.x + 100 && App->player2->positionp2.y <= TankPosition.y) {
//			AngleNotValid = false;
//			App->render->Blit(BossTank, TankPosition.x + 49, TankPosition.y - 6 + Trote, &BigTurretPos5Anim->GetCurrentFrame());// Big TurretAnim
//			App->render->Blit(BossTank, TankPosition.x + 85, TankPosition.y + Trote, &LittleTurretPos4Anim->GetCurrentFrame());// LittleTurretAnim
//		}
//	}
//}
//
//// TURRET SHOOT
//if ((ReachPos1 || ReachPos2) && !LimitReached && !AngleNotValid) {
//	if (TimerShoot >= 75) {
//		App->particles->TankBigShoot.Speed.x = 3 * (cos(Angle1*PI / 180));
//		App->particles->TankBigShoot.Speed.x++;
//		App->particles->TankBigShoot.Speed.y = 3 * (sin(Angle1*PI / 180));
//		App->particles->AddParticle(App->particles->TankBigShoot, TankPosition.x + 44, TankPosition.y - 20, COLLIDER_ENEMY_SHOT);
//		TimerShoot = 0;
//	}
//	if (TimerShoot2 >= 35) {
//		App->particles->BeeShot.Speed.x = 3 * (cos(Angle1*PI / 180));
//		App->particles->BeeShot.Speed.x++;
//		App->particles->BeeShot.Speed.y = 3 * (sin(Angle1*PI / 180));
//		App->particles->AddParticle(App->particles->BeeShot, TankPosition.x + 85, TankPosition.y - 20, COLLIDER_ENEMY_SHOT);
//		TimerShoot2 = 0;
//	}
//}
//
//
//
//return UPDATE_CONTINUE;
//}