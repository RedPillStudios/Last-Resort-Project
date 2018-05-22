#ifndef MODULETANK_H_
#define MODULETANK_H_

#include "Module.h"
#include "p2Point.h"
#include "Animation.h"
#include "Globals.h"
#include <stdio.h>

#include "SDL/include/SDL.h"
#include "SDL/include/SDL_timer.h"
#include <stdlib.h>
#include "ModuleSceneLvl1.h"

struct Collider;
struct SDL_Texture;



class ModuleTank : public Module {

public:

	ModuleTank();
	~ModuleTank();

	bool Start();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	Animation CorriendoAlTrote;
	Animation WaitingPos;
	Animation LidoaTankEngine;
	Animation BigTurretPos1;
	Animation BigTurretPos2;
	Animation BigTurretPos3;
	Animation BigTurretPos4;
	Animation BigTurretPos5;
	Animation LittleTurretPos1;
	Animation LittleTurretPos2;
	Animation LittleTurretPos3;
	Animation LittleTurretPos4;
	


	Animation *WaitingPosAnim = nullptr;
	Animation *CorriendoAlTroteAnim = nullptr;;
	Animation *LidoaTankEngineAnim = nullptr;
	Animation *BigTurretPos1Anim = nullptr;
	Animation *BigTurretPos2Anim = nullptr;
	Animation *BigTurretPos3Anim = nullptr;
	Animation *BigTurretPos4Anim = nullptr;
	Animation *BigTurretPos5Anim = nullptr;
	Animation *LittleTurretPos1Anim = nullptr;
	Animation *LittleTurretPos2Anim = nullptr;
	Animation *LittleTurretPos3Anim = nullptr;
	Animation *LittleTurretPos4Anim = nullptr;
	
public:
	SDL_Texture * BossTank = nullptr;
public:
	fPoint TankPosition;
	iPoint PlayerPos;
public:
	uint life;
	float UpDatePos = 0;
	float Trote = -0.5;
	uint TroteDelay;
	uint Activate = 0;
	
	int TimeInStart;
	int TimeTranscurred;

	uint P1Posx;
	uint P1Posy;
	uint P2Posx;
	uint P2Posy;

	double Radiants1;
	float Angle1;
	double Radiants2;
	float Angle2;
	int TimerShoot = 0;
	int TimerShoot2 = 0;

public:
	bool Movement = false;
	bool TroteInPos = false;
	bool ReachPos1 = false;
	bool ReachPos2 = false;
	bool LimitReached = false;
	bool AngleNotValid = false;
public:
	//Control the position using the time;
	int TimeOnMovement;
};

#endif
