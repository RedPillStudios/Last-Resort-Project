#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleUI.h"
#include "ModuleSceneLvl1.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"

#include<string.h>

ModuleUI::ModuleUI() : Module() {}

ModuleUI::~ModuleUI() {}

bool ModuleUI::Start() {

	if (App->scene1background->IsEnabled() && App->fonts->IsEnabled() == false)
		App->fonts->Enable();

	UI_Main_Menu = App->textures->Load("Images/Stage_Clear/All_Stage_Clears.png");

	//fonts
	font = LoadFont("Images/Fonts/Font_score.png", "0123456789ABCDEFGHIJKLMNPQRSTUVWXYZ_.,[]&$", 2);

	P1Life = 3;
	P2Life = 3;

	return true;
}


bool ModuleUI::CleanUp() {

	App->textures->Unload(UI_Main_Menu);
	App->fonts->UnLoadFont(font);

	return true;
}

update_status ModuleUI::Update() {

	if (Spawned) {

		//PUT FONT
		if (TimeCounter) {
			AppearTime = SDL_GetTicks() + 2000;
			TimeCounter = false;
		}

		App->fonts->BlitText((SCREEN_WIDTH - 98), (SCREEN_HEIGHT - 10), font, "ENEMY");
		App->fonts->BlitText((SCREEN_WIDTH - 56), (SCREEN_HEIGHT - 10), font, "SPAWNED");
		if (SDL_GetTicks() >= AppearTime) {
			TimeCounter = true;
			Spawned = false;
		}
	}

	//P1 Score
	sprintf_s(score_text, "%7d", ScoreP1);
	App->fonts->BlitText(40, 16, font, score_text);
	App->fonts->BlitText(13, 16, font, "P1");
	App->fonts->BlitText(29, 11, font, "_");
	App->fonts->BlitText(29, 15, font, "_");

	App->render->Blit(UI_Main_Menu, 13, 24, &App->player->UI_ship, 0.0f, false); //Mini_UI_Ships->Player1

	//P1 Life
	sprintf_s(life_text, "%7d", P1Life);
	App->fonts->BlitText(30, 24, font, "X0");
	App->fonts->BlitText(-2, 24, font, life_text);

	/*if (App->player2->Dead == true && App->player2->IsEnabled() == false) {
		App->fonts->BlitText((SCREEN_WIDTH - 76), 16, font, "INSERT");
		App->fonts->BlitText((SCREEN_WIDTH - 74), 24, font, "COIN");
	}*/

	//P2 Score
	sprintf_s(score_text2, "%7d", ScoreP2);
	App->fonts->BlitText((SCREEN_WIDTH - 65), 16, font, score_text2);
	App->fonts->BlitText((SCREEN_WIDTH - 76), 11, font, "_");
	App->fonts->BlitText((SCREEN_WIDTH - 76), 15, font, "_");
	App->fonts->BlitText((SCREEN_WIDTH - 92), 16, font, "P2");

	App->render->Blit(UI_Main_Menu, 237, 24, &App->player2->UI_ship2, 0.0f, false); //Mini_UI_Ships->Player2

	//P2 Life
	sprintf_s(life2_text, "%7d", P2Life);
	App->fonts->BlitText((SCREEN_WIDTH - 75), 24, font, "X0");
	App->fonts->BlitText((SCREEN_WIDTH - 107), 24, font, life2_text);

	//TOP Score
	if (App->player2->IsEnabled() == true) {

		uint MaxScore = ScoreP1 + ScoreP2;

		if (MaxScore > TopScore)
			TopScore = MaxScore;
	}
	/*else
	TopScore = App->fonts->TopScoreP1(ScoreP1, TopScore);*/

	sprintf_s(top_score, "%7d", TopScore);

	App->fonts->BlitText((SCREEN_WIDTH / 2) - 41, 16, font, "T0P");
	App->fonts->BlitText((SCREEN_WIDTH / 2) - 9, 16, font, top_score);

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