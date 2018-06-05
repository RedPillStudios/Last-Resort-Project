#ifndef __MODULEHIGHSCORE_H__
#define __MODULEHIGHSCORE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleUI.h"
#include "Application.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

class ModuleHighScore : public Module
{
public:

	ModuleHighScore();
	~ModuleHighScore();
	bool Start();
	update_status Update();
	bool CleanUp();

	SDL_Rect ScoreRect;

public:

	SDL_Texture *Background_HighScoreImage;
	SDL_Texture *HighScore;

	SDL_Rect Background;
	SDL_Rect GameOverImage;

	//Scores
	bool Score;
	uint SumScore;
	char Score1_text[10];
	char Score2_text[10];
	char SumScore_text[10];
	int fontend;

	bool RankBlitted = false;

	bool SubstractCoins = true;

	Mix_Music *GameOver = nullptr;
};


#endif
