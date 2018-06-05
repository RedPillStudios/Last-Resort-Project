#include "ModuleGameControllers.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleMainMenu.h"
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
	
	
	if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0) {
		LOG("Error, gamecontroller fail to initilize",SDL_GetError());
		
	}

	//SDL_GameControllerAddMappingsFromFile(""); -> for adding or own map controller just leaving it here


	
	return ret;
}

// Called every draw update
update_status  ModuleGameControllers::PreUpdate()
{
	//Controller inputs

	for (int i = 0; i < SDL_NumJoysticks(); ++i) {

		if (SDL_IsGameController(i)) {
			if (i == 0) {

				Controller_player1 = SDL_GameControllerOpen(i);
				//Checking if the controller is attached

				if (SDL_GameControllerGetAttached(Controller_player1)) {
					
					//Here we assign the values of the aixis to the integers Controller_Player1_LAxisX...

					Controller_player1_LAxisX = SDL_GameControllerGetAxis(Controller_player1, SDL_CONTROLLER_AXIS_LEFTX);
					Controller_player1_LAxisY = SDL_GameControllerGetAxis(Controller_player1, SDL_CONTROLLER_AXIS_LEFTY);
					
					//Assign the boolean value to the  bools defined  

					controller_player1_A_pressed = SDL_GameControllerGetButton(Controller_player1, SDL_CONTROLLER_BUTTON_A);
				/*	controller_player1_RightShoulder_pressed = SDL_GameControllerGetButton(Controller_player1, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);*/
					controller_player1_Start_pressed = SDL_GameControllerGetButton(Controller_player1, SDL_CONTROLLER_BUTTON_START);
					 controller_player1_B_pressed = SDL_GameControllerGetButton(Controller_player1, SDL_CONTROLLER_BUTTON_B); ;

					Controller_player1_Connected = true;
				}
				
				else {
					
					SDL_GameControllerClose(Controller_player1);
					Controller_player1 = nullptr;
					Controller_player1_Connected = false;

				}
			}
			
			else if (i < 1) {
				
				Controller_player2_Connected = false;
				SDL_GameControllerClose(Controller_player2);
				Controller_player2 = nullptr;

			}

			else if (i == 1 || i == 0 && Controller_player1_Connected == false) {

				Controller_player2 = SDL_GameControllerOpen(i);
				if (SDL_GameControllerGetAttached(Controller_player2)) {

					Controller_player2_LAxisX = SDL_GameControllerGetAxis(Controller_player2, SDL_CONTROLLER_AXIS_LEFTX);
					Controller_player2_LAxisY = SDL_GameControllerGetAxis(Controller_player2, SDL_CONTROLLER_AXIS_LEFTY);

					//Assign the boolean value to the  bools defined  

					controller_player2_A_pressed = SDL_GameControllerGetButton(Controller_player2, SDL_CONTROLLER_BUTTON_A);

				/*	controller_player2_RightShoulder_pressed = SDL_GameControllerGetButton(Controller_player2, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);*/
					controller_player2_Start_pressed = SDL_GameControllerGetButton(Controller_player2, SDL_CONTROLLER_BUTTON_START);
					controller_player2_B_pressed = SDL_GameControllerGetButton(Controller_player2, SDL_CONTROLLER_BUTTON_B);
					Controller_player2_Connected = true;
					break;


				}
				else {

					SDL_GameControllerClose(Controller_player2);
					Controller_player2 = nullptr;
					Controller_player2_Connected = false;

				}
			}
		}
	}
	
	//Check Left Axis X & Y
	if (Controller_player1_LAxisX > 6400) {

		App->input->keyboard[SDL_SCANCODE_D] = KEY_STATE::KEY_REPEAT;

	}
	else if (Controller_player1_LAxisX<-DEATHZONE) {

		App->input->keyboard[SDL_SCANCODE_A] = KEY_STATE::KEY_REPEAT;

	}

	if (Controller_player1_LAxisY < -DEATHZONE) {

		App->input->keyboard[SDL_SCANCODE_W] = KEY_STATE::KEY_REPEAT;

	}
	else if (Controller_player1_LAxisY > DEATHZONE) {

		App->input->keyboard[SDL_SCANCODE_S] = KEY_STATE::KEY_REPEAT;

	}

	//Check controller player one buttons

	if (controller_player1_A_pressed == true && App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_IDLE) {

		App->input->keyboard[SDL_SCANCODE_SPACE] = KEY_STATE::KEY_DOWN;

	}

	else if (controller_player1_A_pressed==true) {
	
		App->input->keyboard[SDL_SCANCODE_SPACE] = KEY_STATE::KEY_REPEAT;
	
	}

	if (controller_player1_Start_pressed == true && App->input->keyboard[SDL_SCANCODE_C] == KEY_STATE::KEY_IDLE) {

		App->input->keyboard[SDL_SCANCODE_C] = KEY_STATE::KEY_DOWN;
	}

	else if (controller_player1_Start_pressed==true)
	App->input->keyboard[SDL_SCANCODE_C] = KEY_STATE::KEY_REPEAT;
	
	if (controller_player1_B_pressed == true && App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_IDLE) {

		App->input->keyboard[SDL_SCANCODE_J] = KEY_STATE::KEY_DOWN;
	}

	else if (controller_player1_B_pressed == true)
		App->input->keyboard[SDL_SCANCODE_J] = KEY_STATE::KEY_REPEAT;

	
	//Check player two axes

	if (Controller_player2_LAxisX > DEATHZONE) {

		App->input->keyboard[SDL_SCANCODE_RIGHT] = KEY_STATE::KEY_REPEAT;

	}
	else if (Controller_player2_LAxisX<-DEATHZONE) {

		App->input->keyboard[SDL_SCANCODE_LEFT] = KEY_STATE::KEY_REPEAT;

	}

	if (Controller_player2_LAxisY < -DEATHZONE) {

		App->input->keyboard[SDL_SCANCODE_UP] = KEY_STATE::KEY_REPEAT;

	}
	else if (Controller_player2_LAxisY > DEATHZONE) {

		App->input->keyboard[SDL_SCANCODE_DOWN] = KEY_STATE::KEY_REPEAT;

	}

	//Check controller player two buttons

	if (controller_player2_A_pressed == true && App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_IDLE) {

		App->input->keyboard[SDL_SCANCODE_RCTRL] = KEY_STATE::KEY_DOWN;

	}

	else if (controller_player2_A_pressed == true) {

		App->input->keyboard[SDL_SCANCODE_RCTRL] = KEY_STATE::KEY_REPEAT;

	}
	
	if (controller_player2_Start_pressed == true && App->input->keyboard[SDL_SCANCODE_C] == KEY_STATE::KEY_IDLE) {

		App->input->keyboard[SDL_SCANCODE_C] = KEY_STATE::KEY_DOWN;
	}

	else if (controller_player2_Start_pressed == true)
		App->input->keyboard[SDL_SCANCODE_C] = KEY_STATE::KEY_REPEAT;
	

	if (controller_player2_B_pressed == true && App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_IDLE) {

		App->input->keyboard[SDL_SCANCODE_J] = KEY_STATE::KEY_DOWN;
	}

	else if (controller_player2_B_pressed == true)
		App->input->keyboard[SDL_SCANCODE_J] = KEY_STATE::KEY_REPEAT;
	
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool  ModuleGameControllers::CleanUp()
{
	
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);

		SDL_GameControllerClose(Controller_player1);
		SDL_GameControllerClose(Controller_player2);
	
		Controller_player1 = nullptr;
		Controller_player2 = nullptr;
	


	return true;
}