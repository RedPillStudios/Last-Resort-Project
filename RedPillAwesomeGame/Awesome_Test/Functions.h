#ifndef FUNCTIONS_H
#define FUNCTIONS_H

bool init() {

	//initialization variable
	bool succes = true;

	//initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	//Create Window(this only creates the "marco" of the windows, here we cannot draw anything)
	window = SDL_CreateWindow("AWESOME GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		succes = false;
	}
	else {
		if (window == NULL) {
			succes = false;
		}
		//Getting the windows.
		Main_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	}

	return succes;
}

void Draw(int SpriteColumn1, int SpriteColumn2, int SpriteColumn3, int PosSprite, int Menuout,int frames) {

	SDL_RenderClear(Main_Renderer);

	SDL_RenderCopy(Main_Renderer, Background_Texture, NULL, &Background);
	SDL_RenderCopy(Main_Renderer, Background_Texture, NULL, &Background2);
	SDL_RenderCopy(Main_Renderer, Impulsor_Texture, &Impulsor_Clipping[frames/4], &Impulsor);
	SDL_RenderCopy(Main_Renderer, Player_shipTexture, NULL, &Ship);
	SDL_RenderCopy(Main_Renderer, Shoot_Texture, NULL, &Shoot);
	SDL_RenderCopy(Main_Renderer, Enemy_shipTexture, NULL, &Enemy);
	SDL_RenderCopy(Main_Renderer, Enemy2_shipTexture, NULL, &Enemy2);
	SDL_RenderCopy(Main_Renderer, Enemy2_ShotTexture, NULL, &Enemy2Shoot);
	SDL_RenderCopy(Main_Renderer, Enemy2_shipTexture, NULL, &Enemy3);
	SDL_RenderCopy(Main_Renderer, Enemy2_ShotTexture, NULL, &Enemy3Shoot);
	SDL_RenderCopy(Main_Renderer, Enemy2_shipTexture, NULL, &Enemy4);
	SDL_RenderCopy(Main_Renderer, Enemy2_ShotTexture, NULL, &Enemy4Shoot);
	SDL_RenderCopy(Main_Renderer, Score_Texture, NULL, &Score);
	SDL_RenderCopy(Main_Renderer, Numbers_Texture, &NumClipper[SpriteColumn3], &Num_1);
	SDL_RenderCopy(Main_Renderer, Numbers_Texture, &NumClipper[SpriteColumn2], &Num_2);
	SDL_RenderCopy(Main_Renderer, Numbers_Texture, &NumClipper[SpriteColumn1], &Num_3);
	SDL_RenderCopy(Main_Renderer, Numbers_Texture, &NumClipper[PosSprite], &Num_4);
	if (Menuout) {
		SDL_RenderCopy(Main_Renderer, GameOver_Texture, NULL, &GameOver);
		SDL_RenderCopy(Main_Renderer, TryAgain_Texture, NULL, &TryAgain);
		SDL_RenderCopy(Main_Renderer, Yes_texture, NULL, &Yes);
		SDL_RenderCopy(Main_Renderer, No_Texture, NULL, &No);
		SDL_RenderCopy(Main_Renderer, Selector_texture, NULL, &Selector);
	}
	SDL_RenderPresent(Main_Renderer);
}

void close() {
	//free loaded images
	SDL_DestroyTexture(Background_Texture);
	Background_Texture = nullptr;
	//Destroy window
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(Main_Renderer);
	window = nullptr;
	Main_Renderer = nullptr;
	//Quit from SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void SpriteSheet(SDL_Rect Sprite[]) {

	for (int i = 1; i < NUMBERS_SHEET; ++i) {
		Sprite[i].x = Sprite[i - 1].x + 73;
		Sprite[i].y = 0;
		Sprite[i].w = 73;
		Sprite[i].h = 102;
	}

}



#endif // !1

