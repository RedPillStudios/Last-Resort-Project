#define _CRT_SECURE_NO_WARNINGS

#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleUI.h"
#include "ModuleSceneLvl1.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleBossLvl1.h"
#include "ModuleMainMenu.h"
#include "ModuleInput.h"
#include "ModuleGameOver.h"
#include "ModuleStageClear.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSound.h"
#include "Module_Hou_Player1.h"
#include "Module_Hou_Player2.h"
#include "ModuleHighScore.h"

#include <iostream>
#include <string.h>
#include <cstdio>

ModuleUI::ModuleUI(){

	Bar.PushBack({0,0,96,8});
	Charge1.PushBack({ 0,10,2,5 });
	Charge2.PushBack({ 0,10,2,5 });

}

ModuleUI::~ModuleUI() {}

bool ModuleUI::Start() {
	Charge_Controller = { 0,10,0,5 };
	Pos_Bar1.x = 30;
	Pos_Bar2.y = 90;

	Bar_Texture = App->textures->Load("Images/Player/HOU_Charger_Sprite.png");

	UI_Main_Menu = App->textures->Load("Images/Stage_Clear/All_Stage_Clears.png");

	//fonts
	font = LoadFont("Images/Fonts/Font_score.png", "0123456789ABCDEFGHIJKLMNPQRSTUVWXYZ_.,[]&$", 2);
	Insert_Coin = App->sound->LoadChunk("Audio/Main_Menu/Insert_Coin.wav");


	Ranking = fopen("Images/Ranking.txt", "r");
	
	if (Ranking != NULL) {

		for (int i = 0; i < 9; i++) {

			fscanf(Ranking, "%c", &ranking[i].name[0]);
			fscanf(Ranking, "%c", &ranking[i].name[1]);
			fscanf(Ranking, "%c", &ranking[i].name[2]);
			fscanf(Ranking, "%d", &ranking[i].score);
		}
	}
	name1 = abecedary[selector];
	name2 = abecedary2[selector2];
	name3 = abecedary3[selector3];
	TopScore = ranking[0].score;
	fclose(Ranking);

	coins = 0;
	return true;
	Current_Bar = &Bar;
}


bool ModuleUI::CleanUp() {

	App->textures->Unload(UI_Main_Menu);
	UnLoadFont(font);
	App->sound->UnloadChunks(Insert_Coin);

	return true;
}

update_status ModuleUI::Update() {

	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) {
		if (GOD == false) {
			GOD = true;
		}
		else if(GOD=true)
			GOD = false;
	}

	if (App->input->keyboard[SDL_SCANCODE_C] == KEY_STATE::KEY_DOWN && coins < 99) {
		coins++;
		Mix_PlayChannel(-1, Insert_Coin, 0);
	}
	if (App->HighScore->IsEnabled() == true) {

		
		if (!ccompleted) {

			if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_DOWN) {

				if (cpressed == false && c2pressed == false && c3pressed == false) {

					name1 = abecedary[selector];
					selector++;
					if (selector > 25)
						selector = 0;
				}
				if (cpressed == true && c2pressed == false && c3pressed == false) {

					name2 = abecedary[selector2];
					selector2++;
					if (selector2 > 25)
						selector2 = 0;
				}
				if (cpressed == true && c2pressed == true && c3pressed == false) {

					name3 = abecedary[selector3];
					selector3++;
					if (selector3 > 25)
						selector3 = 0;
				}
			}
			if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_DOWN) {

				if (cpressed == false && c2pressed == false && c3pressed == false) {
					name1 = abecedary[selector];
					--selector;
					if (selector < 0)
						selector = 25;
				}
				if (cpressed == true && c2pressed == false && c3pressed == false) {

					name2 = abecedary2[selector2];
					--selector2;
					if (selector2 < 0)
						selector2 = 25;
				}
				if (cpressed == true && c2pressed == true && c3pressed == false) {

					name3 = abecedary3[selector3];
					--selector3;
					if (selector3 < 0)
						selector3 = 25;
				}
			}

			if (App->input->keyboard[SDL_SCANCODE_E] == KEY_STATE::KEY_DOWN) {

				if (cpressed == false && cpressed == false && c3pressed == false) {

					NewName[0] = name1;
					cpressed = true;
				}
				else if (cpressed == true && c2pressed == false && c3pressed == false) {

					NewName[1] = name2;
					c2pressed = true;
				}
				else if (c2pressed == true && cpressed == true && c3pressed == false) {

					NewName[2] = name3;
					c3pressed = true;
					ccompleted = true;
					
					for (int i = 0; i < 3; ++i) {

						New[i] = NewName[i];
					}
				}
			}

			BlitText(215, 50, font, &name1);
		}

		
		/*BlitText((SCREEN_WIDTH / 2) + 10, (SCREEN_HEIGHT / 2), font, &c2);
		BlitText((SCREEN_WIDTH / 2) + 20, (SCREEN_HEIGHT / 2), font, &c3);*/
	}

	
		sprintf_s(coins_text, "%7d", coins);
		BlitText((SCREEN_WIDTH - 104), (SCREEN_HEIGHT - 10), font, "CREDITS");
		BlitText((SCREEN_WIDTH - 75), (SCREEN_HEIGHT - 10), font, coins_text);

	if (App->scene1background->IsEnabled()) {

		App->render->Blit(Bar_Texture, 30, SCREEN_HEIGHT - 20, &Bar.GetCurrentFrame(),false);
		if (App->HOU_Player1->charging == true) { 
			if (Charge_Controller.w <= 4060) {
				Charge_Controller.w += 70;
			}
			App->render->Blit(Bar_Texture, 54, SCREEN_HEIGHT - 19, &Charge_Controller, false);
		}
		else{
			Charge_Controller.w = 0;
		}

		if (Spawned) {

			//PUT FONT
			if (TimeCounter) {
				AppearTime = SDL_GetTicks() + 2000;
				TimeCounter = false;
			}

			BlitText((SCREEN_WIDTH - 98), (SCREEN_HEIGHT - 10), font, "ENEMY");
			BlitText((SCREEN_WIDTH - 56), (SCREEN_HEIGHT - 10), font, "SPAWNED");
			if (SDL_GetTicks() >= AppearTime) {
				TimeCounter = true;
				Spawned = false;
			}
		}

		if (P1Life > 0) {
			//P1 Score
			sprintf_s(score_text, "%7d", ScoreP1);
			BlitText(40, 16, font, score_text);
			BlitText(13, 16, font, "P1");
			BlitText(29, 11, font, "_");
			BlitText(29, 15, font, "_");
			
			App->render->Blit(UI_Main_Menu, 13, 24, &App->player->UI_ship, 0.0f, false); //Mini_UI_Ships->Player1

			//P1 Life
			sprintf_s(life_text, "%7d", P1Life);
			BlitText(30, 24, font, "X0");
			BlitText(-2, 24, font, life_text);
		}
		else {

			BlitText(40, 16, font, "DEAD");
			BlitText(13, 16, font, "P1");
		}

		/*if (App->player2->Dead == true && App->player2->IsEnabled() == false) {
			App->fonts->BlitText((SCREEN_WIDTH - 76), 16, font, "INSERT");
			App->fonts->BlitText((SCREEN_WIDTH - 74), 24, font, "COIN");
		}*/

		//P2 Score
		if (App->player2->IsEnabled() == true) {
			sprintf_s(score_text2, "%7d", ScoreP2);
			BlitText((SCREEN_WIDTH - 65), 16, font, score_text2);
			BlitText((SCREEN_WIDTH - 76), 11, font, "_");
			BlitText((SCREEN_WIDTH - 76), 15, font, "_");
			BlitText((SCREEN_WIDTH - 92), 16, font, "P2");
			sprintf_s(life2_text, "%7d", P2Life);
			BlitText((SCREEN_WIDTH - 75), 24, font, "X0");
			BlitText((SCREEN_WIDTH - 107), 24, font, life2_text);

			App->render->Blit(UI_Main_Menu, 237, 24, &App->player2->UI_ship2, 0.0f, false); //Mini_UI_Ships->Player2
		}
		else if (P2Life <= 0) {

			BlitText((SCREEN_WIDTH - 58), 16, font, "DEAD");
			BlitText((SCREEN_WIDTH - 78), 16, font, "P2");
		}
		else {

			BlitText((SCREEN_WIDTH - 20), 16, font, "P2");
			BlitText((SCREEN_WIDTH - 48), 16, font, "F0R");
			BlitText((SCREEN_WIDTH - 58), 16, font, "P");
			BlitText((SCREEN_WIDTH - 100), 16, font, "PRESS");
		}

		//TOP Score
		if (App->scene1background->IsEnabled() == true) {

			uint MaxScore = ScoreP1 + ScoreP2;

			if (MaxScore > TopScore)
				TopScore = MaxScore;
		}
		/*else
		TopScore = App->fonts->TopScoreP1(ScoreP1, TopScore);*/

		sprintf_s(top_score, "%7d", TopScore);

		BlitText((SCREEN_WIDTH / 2) - 41, 16, font, "T0P");
		BlitText((SCREEN_WIDTH / 2) - 9, 16, font, top_score);

		//GOD MODE
		if (GOD) {

			App->fonts->BlitText(13, SCREEN_HEIGHT - 10, App->fonts->font, "G0D");
			App->fonts->BlitText(39, SCREEN_HEIGHT - 10, App->fonts->font, "M0DE");
		}

		if (App->Boss->boss1life) {

			App->fonts->BlitText((SCREEN_WIDTH / 2) - 32, SCREEN_HEIGHT - 10, font, "B0SS");
			App->fonts->BlitText((SCREEN_WIDTH / 2), SCREEN_HEIGHT - 10, font, "1LIFE");
		}
	}

	/*if (Checkpoint1 == true && App->gameover->IsEnabled()) {

		if (App->input->keyboard[SDL_SCANCODE_B] == KEY_STATE::KEY_DOWN) {

			App->fade->FadeToBlack(App->gameover, App->scene1background);
			P1Life = 3;
			P2Life = 3;
		}
	}*/

	
	if ((App->HighScore->IsEnabled() == true) && counterRanking == 0 && ccompleted == true) {

	/*	if (Checkpoint1 == true) {
			BlitText(SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT - 10, font, "B");
			BlitText(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 10, font, "FOR");
			BlitText(SCREEN_WIDTH / 2 + 24, SCREEN_HEIGHT - 10, font, "CONTINUE");
		}*/
		
		uint MaxScore = ScoreP1 + ScoreP2;
		ChangeRanking(Ranking, "Images/Ranking.txt", MaxScore);

		TopScore = ranking[0].score;

		selector = 0;
		selector2 = 0;
		selector3 = 0;

		c2pressed = false;
		c3pressed = false;
		cpressed = false;
		counterRanking++;

	}
	
	return UPDATE_CONTINUE;
}


int ModuleUI::LoadFont(const char* texture_path, const char* characters, uint rows) {

	int id = -1;

	if (texture_path == nullptr || characters == nullptr || rows == 0) {

		LOG("Could not load font");
		return id;
	}

	SDL_Texture* tex = App->textures->Load(texture_path);

	if (tex == nullptr || strlen(characters) >= MAX_FONT_CHARS) {

		LOG("Could not load font at %s with characters '%s'", texture_path, characters);
		return id;
	}

	id = 0;
	for (; id < MAX_FONTS; ++id)
		if (fonts[id].graphic == nullptr)
			break;

	if (id == MAX_FONTS) {

		LOG("Cannot load font %s. Array is full (max %d).", texture_path, MAX_FONTS);
		return id;
	}

	fonts[id].graphic = tex;
	fonts[id].rows = rows;
	fonts[id].len = strlen(characters);

	strcpy_s(fonts[id].table, characters);

	fonts[id].row_chars = strlen(characters) / rows;
	App->textures->GetSize(tex, fonts[id].char_w, fonts[id].char_h);
	fonts[id].char_w /= fonts[id].row_chars;
	fonts[id].char_h /= rows;

	LOG("Successfully loaded BMP font from %s", texture_path);

	return id;
}

void ModuleUI::UnLoadFont(int font_id)
{
	if (font_id >= 0 && font_id < MAX_FONTS && fonts[font_id].graphic != nullptr) {

		App->textures->Unload(fonts[font_id].graphic);
		fonts[font_id].graphic = nullptr;
		LOG("Successfully Unloaded BMP font_id %d", font_id);
	}
}

void ModuleUI::BlitText(int x, int y, int font_id, const char* text) const
{
	if (text == nullptr || font_id < 0 || font_id >= MAX_FONTS || fonts[font_id].graphic == nullptr)
	{
		LOG("Unable to render text with bmp font id %d", font_id);
		return;
	}

	const Font* font = &fonts[font_id];
	SDL_Rect rect;
	uint len = strlen(text);

	rect.w = font->char_w;
	rect.h = font->char_h;

	for (uint i = 0; i < len; ++i)
	{
		uint c = 0;
		for (; c < fonts[font_id].len; ++c)
		{
			if (fonts[font_id].table[c] == text[i])
					break;
		}

		uint col = c % fonts[font_id].row_chars;
		uint row = c / fonts[font_id].row_chars;

		rect.x = col * fonts->char_w;
		rect.y = row * fonts->char_h;

		App->render->Blit(font->graphic, x + i*font->char_w, y, &rect, 1.0f, false);
	}
}

//int ModuleUI::countFile(FILE *pFile, char *path) {
//
//	int counter = 0;
//	pFile = fopen(path, "r");
//
//	if (pFile == NULL) { LOG("error opening file");	}
//	else {
//
//		LOG("Reading file, path: %s", path);
//		while (fgetc(pFile) != EOF) { ++counter; }
//
//		if (feof(pFile)) { LOG("End-of-File reached."); }
//		else { LOG("End-of-File was not reached."); }
//
//		return counter;
//	}
//}

void ModuleUI::ChangeRanking(FILE *pFile, char *path, int Score) {

	for (int i = 0; i < 9; i++) {

		//Changing Array ranking
		if (Score >= ranking[i].score) {

			for (int j = 7; j >= i; j--) {

				ranking[j + 1].score = ranking[j].score;
				ranking[j + 1].name[0] = ranking[j].name[0];
				ranking[j + 1].name[1] = ranking[j].name[1];
				ranking[j + 1].name[2] = ranking[j].name[2];

			}

			/*BlitText((SCREEN_WIDTH - 75), 24, font, "NAME");
			scanf_s("%s", &NewName);*/
			ranking[i].name[0] = New[0];
			ranking[i].name[1] = New[1];
			ranking[i].name[2] = New[2];
			ranking[i].score = Score;
			
			Ranking = fopen("Images/Ranking.txt", "w+");

			if (Ranking != NULL) {

				for (int i = 0; i < 9; i++) {

					fprintf_s(Ranking, "%s", ranking[i].name);
					fprintf_s(Ranking, "%d", ranking[i].score);
				}

				fclose(Ranking);
			}

			break;
		}
	}
}

void ModuleUI::BlitRanking(struct rank array[9]) {

	char NameScore[10];
	int BlitY = 50;

	for (int i = 0; i < 9; i++) {

		sprintf(NameScore, "%7d", ranking[i].score);

		BlitText(125, BlitY, font, NameScore);
		BlitText(215, BlitY, font, ranking[i].name);
		BlitY += 16;
	}

	BlitText(215, 194, font, "RCK");
	BlitText(133, 194, font, "0VER9000");

	App->HighScore->RankBlitted = true;
}