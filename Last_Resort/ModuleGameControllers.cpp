#include "ModuleGameControllers.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"


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
	
	if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0 || SDL_NumJoysticks() < 1) {
		LOG("Error, gamecontroller fail to initilize",SDL_GetError());
		
	}


	for (int i = 0; i < SDL_NumJoysticks(); i++){

		if (i > MAX_GAME_CONTROLLERS) {
			break;
		}

		if (SDL_IsGameController(i)){

			PlayerController[i] = SDL_GameControllerOpen(i);//initializing the first controller
			LOG("%d",SDL_GameControllerName);
			LOG(SDL_GameControllerMapping(PlayerController[i]));
			
		}

	}

	//SDL_GameControllerAddMappingsFromFile(""); -> for adding or own map controller just leaving it here


	
	return ret;
}

// Called every draw update
update_status  ModuleGameControllers::PreUpdate()
{

	while (SDL_PollEvent(&event_)!=0) {

			//COndition if there is movement in the joystick axes
			/*if (event_.type ==SDL_CONTROLLERAXISMOTION ) {

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

			}*/

			//game controller buttons input

			if (event_.type == SDL_CONTROLLERBUTTONDOWN) {
				
				LOG("%d", (int)event_.cbutton.button);

				if (event_.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
						//do this
					App->input->keyboard[SDL_SCANCODE_SPACE] = KEY_DOWN;
				}
				if (event_.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) {

					//do this

				}



			}

		}

		

	
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool  ModuleGameControllers::CleanUp()
{
	LOG("Cleanning moduleGameController")

		for (int i = 0; i < MAX_GAME_CONTROLLERS; ++i)
		{
			if (PlayerController[i] != nullptr) {
				SDL_GameControllerClose(PlayerController[i]);
			}

			PlayerController[i] = nullptr;

		}

	return true;
}