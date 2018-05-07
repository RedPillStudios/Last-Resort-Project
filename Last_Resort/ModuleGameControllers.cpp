#include "ModuleGameControllers.h"
#include "ModuleInput.h"


ModuleGameControllers::ModuleGameControllers():Module()
{
	
}


ModuleGameControllers::~ModuleGameControllers()
{
}
bool ModuleGameControllers::Init()
{
	LOG("Init gamepads");
	bool ret = true;

	SDL_Init(SDL_INIT_GAMECONTROLLER);
	
	if (SDL_NumJoysticks() < 1) {
		LOG("there is no controller connected");
		ret = false;
	}
	else {


	for (int i = 0; i < SDL_NumJoysticks(); i++){

		if (SDL_IsGameController(i)){

			PlayerController = SDL_GameControllerOpen(i);//initializing the first controller
			LOG("%d",SDL_GameControllerName);
			LOG(SDL_GameControllerMapping(PlayerController));
			break;
		}

	}

	//SDL_GameControllerAddMappingsFromFile(""); -> for adding or own map controller just leaving it here


	}
	return ret;
}

// Called every draw update
update_status  ModuleGameControllers::PreUpdate()
{

	while (SDL_PollEvent(&event_)!=0) {

			//COndition if there is movement in the joystick axes
			if (event_.type ==SDL_CONTROLLERAXISMOTION ) {

				if(event_.jaxis.which==0){
				
					if (event_.jaxis.axis == 0) {

						LOG("%d",event_.jaxis.value)

						if (event_.jaxis.value > 8000) {
							return update_status::UPDATE_STOP;

						}
						else if (event_.jaxis.value < -8000) {

							return update_status::UPDATE_STOP;
						}
						
					}
			
				}

			}

			if (event_.type == SDL_CONTROLLERBUTTONDOWN) {
				
				LOG("%d", (int)event_.jbutton.button);

				if (event_.jbutton.button == SDL_CONTROLLER_BUTTON_A) {
					

					//if (event_.jbutton.button == 0) {


					//	//do this
					//}

				}

			}

		}

		

	
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool  ModuleGameControllers::CleanUp()
{
	if (PlayerController != NULL) {
		SDL_GameControllerClose(PlayerController);
		PlayerController = nullptr;

	}
	

	return true;
}