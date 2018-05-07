#include "Module.h"
#include "Globals.h"
#include "SDL/include/SDL.h"
#include "SDL/include/SDL_scancode.h"


#define MAX_BUTTONS 150

class ModuleGameControllers:public Module
{
public:
	ModuleGameControllers();
	~ModuleGameControllers();


	bool Init();
	update_status PreUpdate();
	bool CleanUp();
	SDL_Event event_;

	SDL_GameController*PlayerController = nullptr;



};

