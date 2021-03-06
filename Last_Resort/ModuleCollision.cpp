#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

ModuleCollision::ModuleCollision()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;


	matrix[COLLIDER_NONE][COLLIDER_WALL] = false;
	matrix[COLLIDER_NONE][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_NONE][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_NONE][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_NONE][COLLIDER_PLAYER_SHOT2] = false;
	matrix[COLLIDER_NONE][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_NONE][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_NONE][COLLIDER_HOU] = false;
	matrix[COLLIDER_NONE][COLLIDER_CAR] = false;
	matrix[COLLIDER_NONE][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_NONE][COLLIDER_PLAYER_LASERBEAM_SHOT] = false;
	matrix[COLLIDER_NONE][COLLIDER_PLAYER_LASERBEAM_SHOT2] = false;
	matrix[COLLIDER_NONE][COLLIDER_PLAYER_LASERBEAM_AREA_SHOT] = false;
	matrix[COLLIDER_NONE][COLLIDER_PLAYER_LASERBEAM_AREA_SHOT2] = false;





	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_SHOT2] = false;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_WALL][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_WALL][COLLIDER_HOU] = false;
	matrix[COLLIDER_WALL][COLLIDER_CAR] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_LASERBEAM_SHOT] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_LASERBEAM_SHOT2] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_LASERBEAM_AREA_SHOT] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_LASERBEAM_AREA_SHOT2] = false;
	matrix[COLLIDER_WALL][COLLIDER_NONE] = false;

	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_SHOT2] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_POWER_UP] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_HOU] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_CAR] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_LASERBEAM_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_LASERBEAM_SHOT2] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_LASERBEAM_AREA_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_LASERBEAM_AREA_SHOT2] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_NONE] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_BOSS_SHOOT] = true;

	matrix[COLLIDER_PLAYER2][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_PLAYER_SHOT2] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_POWER_UP] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_HOU] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_CAR] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_PLAYER_LASERBEAM_SHOT] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_PLAYER_LASERBEAM_SHOT2] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_PLAYER_LASERBEAM_AREA_SHOT] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_PLAYER_LASERBEAM_AREA_SHOT2] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_NONE] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_BOSS_SHOOT] = true;

	matrix[COLLIDER_ENEMY][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_SHOT2] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_HOU] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_CAR] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_LASERBEAM_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_LASERBEAM_SHOT2] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_LASERBEAM_AREA_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_LASERBEAM_AREA_SHOT2] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_NONE] = false;

	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_WALL] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_SHOT2] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_HOU] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_CAR] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_LASERBEAM_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_LASERBEAM_SHOT2] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_LASERBEAM_AREA_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_LASERBEAM_AREA_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_NONE] = false;



	matrix[COLLIDER_PLAYER_SHOT2][COLLIDER_WALL] = false;
	matrix[COLLIDER_PLAYER_SHOT2][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_SHOT2][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_SHOT2][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT2][COLLIDER_PLAYER_SHOT2] = false;
	matrix[COLLIDER_PLAYER_SHOT2][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER_SHOT2][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_PLAYER_SHOT2][COLLIDER_HOU] = false;
	matrix[COLLIDER_PLAYER_SHOT2][COLLIDER_CAR] = true;
	matrix[COLLIDER_PLAYER_SHOT2][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_PLAYER_SHOT2][COLLIDER_PLAYER_LASERBEAM_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT2][COLLIDER_PLAYER_LASERBEAM_SHOT2] = false;
	matrix[COLLIDER_PLAYER_SHOT2][COLLIDER_PLAYER_LASERBEAM_AREA_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT2][COLLIDER_PLAYER_LASERBEAM_AREA_SHOT2] = false;
	matrix[COLLIDER_PLAYER_SHOT2][COLLIDER_NONE] = false;

	
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_SHOT2] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_HOU] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_CAR] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_LASERBEAM_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_LASERBEAM_SHOT2] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_LASERBEAM_AREA_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_LASERBEAM_AREA_SHOT2] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_NONE] = false;

	matrix[COLLIDER_POWER_UP][COLLIDER_WALL] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_POWER_UP][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_PLAYER_SHOT2] =false;
	matrix[COLLIDER_POWER_UP][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_HOU] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_POWER_UP][COLLIDER_PLAYER_LASERBEAM_SHOT] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_PLAYER_LASERBEAM_SHOT2] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_PLAYER_LASERBEAM_AREA_SHOT] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_PLAYER_LASERBEAM_AREA_SHOT2] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_NONE] = false;

	matrix[COLLIDER_HOU][COLLIDER_WALL] = false;
	matrix[COLLIDER_HOU][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_HOU][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_HOU][COLLIDER_ENEMY_SHOT] =true;
	matrix[COLLIDER_HOU][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_HOU][COLLIDER_PLAYER_SHOT2] = false;
	matrix[COLLIDER_HOU][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_HOU][COLLIDER_HOU] = false;
    matrix[COLLIDER_HOU][COLLIDER_CAR] =true;
	matrix[COLLIDER_HOU][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_HOU][COLLIDER_PLAYER_LASERBEAM_SHOT] = false;
	matrix[COLLIDER_HOU][COLLIDER_PLAYER_LASERBEAM_SHOT2] = false;
	matrix[COLLIDER_HOU][COLLIDER_PLAYER_LASERBEAM_AREA_SHOT] = false;
	matrix[COLLIDER_HOU][COLLIDER_PLAYER_LASERBEAM_AREA_SHOT2] = false;
	matrix[COLLIDER_HOU][COLLIDER_NONE] = false;
	matrix[COLLIDER_HOU][COLLIDER_BOSS_SHOOT];

	matrix[COLLIDER_CAR][COLLIDER_WALL] = false;
	matrix[COLLIDER_CAR][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_CAR][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_CAR][COLLIDER_PLAYER_SHOT2] = true;
	matrix[COLLIDER_CAR][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_CAR][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_CAR][COLLIDER_CAR] = false;
    matrix[COLLIDER_CAR][COLLIDER_HOU] = false;
	matrix[COLLIDER_CAR][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_CAR][COLLIDER_PLAYER_LASERBEAM_SHOT] = true;
	matrix[COLLIDER_CAR][COLLIDER_PLAYER_LASERBEAM_SHOT2] = true;
	matrix[COLLIDER_CAR][COLLIDER_PLAYER_LASERBEAM_AREA_SHOT] = true;
	matrix[COLLIDER_CAR][COLLIDER_PLAYER_LASERBEAM_AREA_SHOT2] = true;
	matrix[COLLIDER_CAR][COLLIDER_NONE] = false;

	matrix[COLLIDER_PLAYER_LASERBEAM_SHOT][COLLIDER_WALL] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_LASERBEAM_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_SHOT][COLLIDER_PLAYER_SHOT2] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_SHOT][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_SHOT][COLLIDER_HOU] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_SHOT][COLLIDER_CAR] = true;
	matrix[COLLIDER_PLAYER_LASERBEAM_SHOT][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_SHOT][COLLIDER_NONE] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_SHOT][COLLIDER_PLAYER_LASERBEAM_SHOT2] = false;


	matrix[COLLIDER_PLAYER_LASERBEAM_SHOT2][COLLIDER_WALL] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_SHOT2][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_SHOT2][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_LASERBEAM_SHOT2][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_SHOT2][COLLIDER_PLAYER_SHOT2] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_SHOT2][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_SHOT2][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_SHOT2][COLLIDER_HOU] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_SHOT2][COLLIDER_CAR] = true;
	matrix[COLLIDER_PLAYER_LASERBEAM_SHOT2][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_SHOT2][COLLIDER_NONE] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_SHOT2][COLLIDER_PLAYER_LASERBEAM_SHOT] = false;

	//COLLIDER_PLAYER_LASERBEAM_AREA_SHOT

	matrix[COLLIDER_PLAYER_LASERBEAM_AREA_SHOT][COLLIDER_WALL] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_AREA_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_AREA_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_LASERBEAM_AREA_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_AREA_SHOT][COLLIDER_PLAYER_SHOT2] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_AREA_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_AREA_SHOT][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_AREA_SHOT][COLLIDER_HOU] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_AREA_SHOT][COLLIDER_CAR] = true;
	matrix[COLLIDER_PLAYER_LASERBEAM_AREA_SHOT][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_AREA_SHOT][COLLIDER_NONE] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_AREA_SHOT][COLLIDER_PLAYER_LASERBEAM_AREA_SHOT2] = false;


	matrix[COLLIDER_PLAYER_LASERBEAM_AREA_SHOT2][COLLIDER_WALL] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_AREA_SHOT2][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_AREA_SHOT2][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_LASERBEAM_AREA_SHOT2][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_AREA_SHOT2][COLLIDER_PLAYER_SHOT2] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_AREA_SHOT2][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_AREA_SHOT2][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_AREA_SHOT2][COLLIDER_HOU] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_AREA_SHOT2][COLLIDER_CAR] = true;
	matrix[COLLIDER_PLAYER_LASERBEAM_AREA_SHOT2][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_AREA_SHOT2][COLLIDER_PLAYER_LASERBEAM_AREA_SHOT] = false;
	matrix[COLLIDER_PLAYER_LASERBEAM_AREA_SHOT][COLLIDER_PLAYER_LASERBEAM_AREA_SHOT2] = false;

	matrix[COLLIDER_PLAYER_LASERBEAM_AREA_SHOT][COLLIDER_NONE] = false;

	matrix[COLLIDER_BOSS_SHOOT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_BOSS_SHOOT][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_BOSS_SHOOT][COLLIDER_HOU] = true;
}

// Destructor
ModuleCollision::~ModuleCollision() {}

update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
 		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	// Calculate collisions
	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->CheckCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->callback)
				c2->callback->OnCollision(c2, c1);
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleCollision::Update()
{

	DebugDraw();
	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	if (App->input->keyboard[SDL_SCANCODE_F1] == KEY_DOWN)
		debug = !debug;

	if (debug == false)

		return;

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case COLLIDER_PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case COLLIDER_PLAYER2:
			App->render->DrawQuad(colliders[i]->rect, 0, 100, 0, alpha);
			break;
		case COLLIDER_ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_PLAYER_SHOT2: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_ENEMY_SHOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case COLLIDER_POWER_UP: //Orange
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 128, alpha);
			break;
		case COLLIDER_HOU://Pink
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 255, alpha);
		case COLLIDER_CAR: // magenta
			App->render->DrawQuad(colliders[i]->rect, 155, 155, 255, alpha);
		case COLLIDER_PLAYER_LASERBEAM_SHOT:
			App->render->DrawQuad(colliders[i]->rect, 33, 33, 66, alpha);
		case COLLIDER_PLAYER_LASERBEAM_SHOT2:
			App->render->DrawQuad(colliders[i]->rect, 33, 33, 66, alpha);
		case COLLIDER_PLAYER_LASERBEAM_AREA_SHOT:
			App->render->DrawQuad(colliders[i]->rect, 99, 68, 4, alpha);
		case COLLIDER_PLAYER_LASERBEAM_AREA_SHOT2:
			App->render->DrawQuad(colliders[i]->rect, 99, 68, 4, alpha);
		case COLLIDER_BOSS_SHOOT:
			App->render->DrawQuad(colliders[i]->rect, 155, 155, 30, alpha);
		}
	}
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	if ((r.x + r.w) < rect.x || (r.y + r.h) < rect.y || r.x > (rect.x + rect.w) || r.y > (rect.y + rect.h)) { return false; }
	return true;
}

