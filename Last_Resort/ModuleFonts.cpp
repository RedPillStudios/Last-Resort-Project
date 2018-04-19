#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFonts.h"

#include<string.h>

ModuleFonts::ModuleFonts() : Module() {}

ModuleFonts::~ModuleFonts() {}

int ModuleFonts::Load(const char* texture_path, const char* characters, uint rows) {

	int id = -1;

	if (texture_path == nullptr || characters == nullptr || rows == 0)
	{
		LOG("Could not load font");
		return id;
	}

	SDL_Texture* tex = App->textures->Load(texture_path);

	if (tex == nullptr || strlen(characters) >= MAX_FONT_CHARS)
	{
		LOG("Could not load font at %s with characters '%s'", texture_path, characters);
		return id;
	}

	id = 0;
	for (; id < MAX_FONTS; ++id)
		if (fonts[id].graphic == nullptr)
			break;

	if (id == MAX_FONTS)
	{
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

void ModuleFonts::UnLoad(int font_id)
{
	if (font_id >= 0 && font_id < MAX_FONTS && fonts[font_id].graphic != nullptr)
	{
		App->textures->Unload(fonts[font_id].graphic);
		fonts[font_id].graphic = nullptr;
		LOG("Successfully Unloaded BMP font_id %d", font_id);
	}
}

void ModuleFonts::BlitText(int x, int y, int font_id, const char* text) const
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

uint ModuleFonts::TopScore(uint Score1, uint Score2, uint TopScore) {

	uint MaxScore;
	if (Score1 >= Score2)
		MaxScore = Score1;
	else
		MaxScore = Score2;
	
	if (MaxScore > TopScore)
		TopScore = MaxScore;

	return TopScore;
}

uint ModuleFonts::TopScoreP1(uint Score1, uint TopScore) {

	if (Score1 > TopScore)
		TopScore = Score1;

	return TopScore;
}