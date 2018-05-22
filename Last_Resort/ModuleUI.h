#ifndef ModuleUI_H
#define ModuleUI_H

#include "Module.h"
#include "SDL/include/SDL_pixels.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")
#include <stdio.h>
#include <cstdio>

#define MAX_FONTS 10
#define MAX_FONT_CHARS 256

struct SDL_Texture;

struct Font {

	char table[MAX_FONT_CHARS];
	SDL_Texture* graphic = nullptr;
	uint rows, len, char_w, char_h, row_chars;
};

struct rank {

	char name[4] = "NON";
	int score = 0;
};

class ModuleUI : public Module {

public:

	ModuleUI();
	~ModuleUI();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	int LoadFont(const char* texture_path, const char *characters, uint rows = 1);
	void UnLoadFont(int font_id);
	void BlitText(int x, int y, int bmp_font_id, const char *text) const;

	Mix_Chunk *Insert_Coin = nullptr;	

public:

	//Scores & UI
	//uint TopScoreP1(uint Score1, uint TopScore);

	bool Spawned;
	bool TimeCounter = true;
	uint AppearTime;
	uint current_time = SDL_GetTicks();

	SDL_Texture*UI_Main_Menu = nullptr;

	//Font id
	int font = -1;

	//P1 Score
	char score_text[10];
	uint ScoreP1;

	//P2 Score
	char score_text2[10];
	uint ScoreP2;

	//Top Score
	char top_score[10];
	uint TopScore;

	//P1 Life
	char life_text[10];
	uint P1Life;

	//P2 Life
	char life2_text[10];
	uint P2Life;

	//Coins
	int coins;
	char coins_text[10];

	//Checkpoints
	bool Checkpoint1 = false;

	//RANKING
	FILE *Ranking;
	int countFile(FILE *pFile, char *path);
	

private:

	Font fonts[MAX_FONTS];
};

#endif