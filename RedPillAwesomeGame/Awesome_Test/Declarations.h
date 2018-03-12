#ifndef DECLA_H
#define DECLA_H

#define SHAPE_SIZE 100
#define PLSHOOT 30
#define SCORE_SIZEX 150
#define SCORE_SIZEY 50
#define OUTSCREEN 800

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int NUMBERS_SHEET = 10;
const int ANIM_FRAMES = 5;
SDL_Event e;


SDL_Rect Background;
SDL_Rect Background2;
SDL_Rect Ship;
SDL_Rect Shoot;
SDL_Rect Enemy;
SDL_Rect Enemy2;
SDL_Rect Enemy3;
SDL_Rect Enemy4;
SDL_Rect Enemy2Shoot;
SDL_Rect Enemy3Shoot;
SDL_Rect Enemy4Shoot;
SDL_Rect Score;
SDL_Rect NumClipper[NUMBERS_SHEET];
SDL_Rect Num_1;
SDL_Rect Num_2;
SDL_Rect Num_3;
SDL_Rect Num_4;
SDL_Rect GameOver;
SDL_Rect TryAgain;
SDL_Rect Yes;
SDL_Rect No;
SDL_Rect Selector;
SDL_Rect Impulsor;
SDL_Rect Impulsor_Clipping[ANIM_FRAMES];


void Set_Initial_States() {

	Impulsor.x=NULL;
	Impulsor.y = NULL;
	Impulsor.w=190;
	Impulsor.h = 40;

	Impulsor_Clipping[0].x = 0;
	Impulsor_Clipping[0].y = 0;
	Impulsor_Clipping[0].w = 266;
	Impulsor_Clipping[0].h = 133;

	Impulsor_Clipping[1].x = 266;
	Impulsor_Clipping[1].y = 0;
	Impulsor_Clipping[1].w = 266;
	Impulsor_Clipping[1].h = 133;

	Impulsor_Clipping[2].x = 532;
	Impulsor_Clipping[2].y = 0;
	Impulsor_Clipping[2].w = 266;
	Impulsor_Clipping[2].h = 133;

	Impulsor_Clipping[3].x = 798;
	Impulsor_Clipping[3].y = 0;
	Impulsor_Clipping[3].w = 266;
	Impulsor_Clipping[3].h = 133;

	Impulsor_Clipping[4].x = 1064;
	Impulsor_Clipping[4].y = 0;
	Impulsor_Clipping[4].w = 266;
	Impulsor_Clipping[4].h = 133;


	Background.x = 0;
	Background.y = 0;
	Background.w = SCREEN_WIDTH;
	Background.h = SCREEN_HEIGHT;

	Background2.x = SCREEN_WIDTH;
	Background2.y = 0;
	Background2.w = SCREEN_WIDTH;
	Background2.h = SCREEN_HEIGHT;

	NumClipper[0].x = 0;
	NumClipper[0].y = 0;
	NumClipper[0].w = 73;
	NumClipper[0].h = 102;

	Num_1.x = 150;
	Num_1.y = 0;
	Num_1.w = 30;
	Num_1.h = 50;

	Num_2.x = 180;
	Num_2.y = 0;
	Num_2.w = 30;
	Num_2.h = 50;

	Num_3.x = 210;
	Num_3.y = 0;
	Num_3.w = 30;
	Num_3.h = 50;

	Num_4.x = 240;
	Num_4.y = 0;
	Num_4.w = 30;
	Num_4.h = 50;

	Score.w = SCORE_SIZEX;
	Score.h = SCORE_SIZEY;
	Score.x = 0;
	Score.y = 0;


	Shoot.w = PLSHOOT;
	Shoot.h = PLSHOOT;
	Shoot.x = OUTSCREEN;
	Shoot.y = OUTSCREEN;

	Score.w = SCORE_SIZEX;
	Score.h = SCORE_SIZEY;
	Score.x = 0;
	Score.y = 0;

	Ship.x = 200;
	Ship.y = 200;
	Ship.w = 70;
	Ship.h = 40;

	Enemy.x = SCREEN_WIDTH;
	Enemy.y = rand() % (SCREEN_HEIGHT - 100) + 100;
	Enemy.w = 100;
	Enemy.h = 50;

	Enemy2.x = SCREEN_WIDTH * 2;
	Enemy2.y = 40;
	Enemy2.w = SHAPE_SIZE;
	Enemy2.h = 50;

	Enemy3.x = SCREEN_WIDTH * 2;
	Enemy3.y = 200;
	Enemy3.w = SHAPE_SIZE;
	Enemy3.h = 50;

	Enemy4.x = SCREEN_WIDTH * 2;
	Enemy4.y = 360;
	Enemy4.w = SHAPE_SIZE;
	Enemy4.h = 50;

	Enemy2Shoot.x = OUTSCREEN;
	Enemy2Shoot.y = OUTSCREEN;
	Enemy2Shoot.w = PLSHOOT;
	Enemy2Shoot.h = PLSHOOT;

	Enemy3Shoot.x = OUTSCREEN;
	Enemy3Shoot.y = OUTSCREEN;
	Enemy3Shoot.w = PLSHOOT;
	Enemy3Shoot.h = PLSHOOT;

	Enemy4Shoot.x = OUTSCREEN;
	Enemy4Shoot.y = OUTSCREEN;
	Enemy4Shoot.w = PLSHOOT;
	Enemy4Shoot.h = PLSHOOT;

	GameOver.x = 30;
	GameOver.y = NULL;
	GameOver.w = 600;
	GameOver.h = 250;

	TryAgain.x = 80;
	TryAgain.y = 100;
	TryAgain.w = 500;
	TryAgain.h = 200;

	Yes.x = 150;
	Yes.y = 330;
	Yes.w = 100;
	Yes.h = 60;

	No.x = 400;
	No.y = 330;
	No.w = 70;
	No.h = 60;

	Selector.x = OUTSCREEN;
	Selector.y = 340;
	Selector.w = 35;
	Selector.h = 35;


}



#endif // !1


