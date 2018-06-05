#ifndef __MODULEGAMEOVER_H__
#define __MODULEGAEMOVER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

class ModuleGameOver : public Module
{
public:
	
	ModuleGameOver();
	~ModuleGameOver();
	bool Start();
	update_status Update();
	bool CleanUp();

	SDL_Rect ScoreRect;

public:

	SDL_Texture *graphics_GameOverImage;

	SDL_Rect Background;
	SDL_Rect GameOverImage;

	//Scores
	bool Score;
	uint SumScore;
	char Score1_text[10];
	char Score2_text[10];
	char SumScore_text[10];
	int fontend;

	bool SubstractCoins = true;

	Mix_Music *GameOver = nullptr;
};


#endif
