#include "Module.h"
#include "Globals.h"
#include "SDL/include/SDL.h"
#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL_gamecontroller.h"

#define MAX_BUTTONS 150
#define MAX_GAME_CONTROLLERS 2

class ModuleGameControllers:public Module
{
public:
	ModuleGameControllers();
	~ModuleGameControllers();


	bool Init();
	update_status PreUpdate();
	bool CleanUp();
	SDL_Event event_;

	SDL_GameController*PlayerController[MAX_GAME_CONTROLLERS] = { nullptr };



};

