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

#include <iostream>
#include <string.h>
#include <cstdio>

ModuleUI::ModuleUI() : Module() {}

ModuleUI::~ModuleUI() {}

bool ModuleUI::Start() {

	UI_Main_Menu = App->textures->Load("Images/Stage_Clear/All_Stage_Clears.png");

	//fonts
	font = LoadFont("Images/Fonts/Font_score.png", "0123456789ABCDEFGHIJKLMNPQRSTUVWXYZ_.,[]&$", 2);
	Insert_Coin = App->sound->LoadChunk("Audio/Main_Menu/Insert_Coin.wav");
	Mix_VolumeChunk(Insert_Coin, MIX_MAX_VOLUME / 2);

	ScoreP1 = 0;
	ScoreP2 = 0;
	P1Life = 3;
	P2Life = 3;
	coins = 0;

	return true;
}


bool ModuleUI::CleanUp() {

	App->textures->Unload(UI_Main_Menu);
	UnLoadFont(font);
	App->sound->UnloadChunks(Insert_Coin);

	return true;
}

update_status ModuleUI::Update() {


	if (App->input->keyboard[SDL_SCANCODE_C] == KEY_STATE::KEY_DOWN && coins < 100) {
		coins++;
		Mix_PlayChannel(-1, Insert_Coin, 0);
	}

		sprintf_s(coins_text, "%7d", coins);
		BlitText((SCREEN_WIDTH - 104), (SCREEN_HEIGHT - 10), font, "CREDITS");
		BlitText((SCREEN_WIDTH - 75), (SCREEN_HEIGHT - 10), font, coins_text);

	if (App->scene1background->IsEnabled()) {

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

		/*if (App->player2->Dead == true && App->player2->IsEnabled() == false) {
			App->fonts->BlitText((SCREEN_WIDTH - 76), 16, font, "INSERT");
			App->fonts->BlitText((SCREEN_WIDTH - 74), 24, font, "COIN");
		}*/

		//P2 Score
		sprintf_s(score_text2, "%7d", ScoreP2);
		BlitText((SCREEN_WIDTH - 65), 16, font, score_text2);
		BlitText((SCREEN_WIDTH - 76), 11, font, "_");
		BlitText((SCREEN_WIDTH - 76), 15, font, "_");
		BlitText((SCREEN_WIDTH - 92), 16, font, "P2");

		App->render->Blit(UI_Main_Menu, 237, 24, &App->player2->UI_ship2, 0.0f, false); //Mini_UI_Ships->Player2

		//P2 Life
		sprintf_s(life2_text, "%7d", P2Life);
		BlitText((SCREEN_WIDTH - 75), 24, font, "X0");
		BlitText((SCREEN_WIDTH - 107), 24, font, life2_text);

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
		if (App->player->GOD || App->player2->GOD) {

			App->fonts->BlitText(13, SCREEN_HEIGHT - 10, App->fonts->font, "G0D");
			App->fonts->BlitText(39, SCREEN_HEIGHT - 10, App->fonts->font, "M0DE");
		}

		if (App->Boss->boss1life) {

			App->fonts->BlitText((SCREEN_WIDTH / 2) - 32, SCREEN_HEIGHT - 10, font, "B0SS");
			App->fonts->BlitText((SCREEN_WIDTH / 2), SCREEN_HEIGHT - 10, font, "1LIFE");
		}

	}

	if (Checkpoint1 == true && App->gameover->IsEnabled()) {

		if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN) {

			App->fade->FadeToBlack(App->gameover, App->scene1background);
			P1Life = 3;
			P2Life = 3;
		}
	}

	if (App->gameover->IsEnabled() || App->stageclear->IsEnabled()) {

		struct rank ranking[10];
		char NewName[3];

		BlitText((SCREEN_WIDTH - 75), 24, font, "NAME");
		scanf_s("%s", &NewName);

		Ranking = fopen("Images/Ranking.txt", "w");

		if (Ranking != NULL) {

			int a = countFile(Ranking, "Images/Ranking.txt");

			if (a == 0) {

				for (int i = 0; i < 10; i++) {
					
					fprintf(Ranking, "%s", ranking[i].name);
					fprintf(Ranking, "%d", ranking[i].score);
				}
			}

			/*for (int i = 0; i < 9; i++) {

				fscanf(Ranking, "%d", &ranking[i].score);
				fscanf(Ranking, "%s", &ranking[i].name);

				if (TopScore >= ranking[i].score) {

					for (int j = 8; j >= i; j--) {

						ranking[j + 1].score = ranking[j].score;
						ranking[j + 1].name[1] = ranking[j].name[1];
						ranking[j + 1].name[2] = ranking[j].name[2];
						ranking[j + 1].name[3] = ranking[j].name[3];
					}

					ranking[i].score = TopScore;
					ranking[i].name[1] = NewName[1];
					ranking[i].name[2] = NewName[2];
					ranking[i].name[3] = NewName[3];
					break;
				}
			}

			for (int i = 0; i < 9; i++)
				fprintf(Ranking, "\n %s %d \n", ranking[i].name, ranking[i].score);*/

			fclose(Ranking);
		}
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

int ModuleUI::countFile(FILE *pFile, char *path) {

	int counter = 0;
	pFile = fopen(path, "r");

	if (pFile == NULL) { LOG("error opening file");	}
	else {

		LOG("Reading file, path: %s", path);
		while (fgetc(pFile) != EOF) { ++counter; }

		if (feof(pFile)) { LOG("End-of-File reached."); }
		else { LOG("End-of-File was not reached."); }

		return counter;

	}
}