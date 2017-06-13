#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleSceneSpace.h"






ModulePlayer::ModulePlayer()
{
	idle.SetUp(10, 16, 49, 60, 4, 4, "0,1,2,3");
	idle.speed = 0.1f;



	up.SetUp(10, 16, 49, 60, 4, 4, "0,1,2,3");
	up.speed = 0.1f;



	down.SetUp(8, 380, 50, 50, 3, 3, "0,1,2");
	down.speed = 0.1f;



	punch.SetUp(0, 448, 70, 56, 6, 6, "1,3,5");
	punch.speed = 0.5f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("rtype/sprites-finales.png");

	position.x = 150;
	position.y = 120;

	// TODO 2: Add a collider to the player
	
	
	collider_offset.x = 5;
	collider_offset.y = 0;
	player_collider = App->collision->AddCollider({0, 0, 40, 55}, COLLIDER_PLAYER, this);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	if (player_collider != nullptr)
		player_collider->to_delete = true;

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 2;

	if(App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		position.x -= speed;
	}

	if(App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		position.x += speed;
	}

	if(App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		
		if(current_animation != &down)
		{
			/*down.Reset();*/
			current_animation = &down;
		}
	}

	if(App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		
		if(current_animation != &up)
		{
			up.Reset();
			current_animation = &up;
		}
	}

	if(App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		
		current_animation = &punch;
	}

	if(App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
	   && App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE)
		current_animation = &idle;



	// TODO 3: Update collider position to player position
	player_collider->SetPos(position.x + collider_offset.x, position.y + collider_offset.y);
	
	// Draw everything --------------------------------------
	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}

// TODO 4: Detect collision with a wall. If so, go back to intro screen.
 
void ModulePlayer::OnCollision( Collider* c1, Collider* c2)
{
	
	if (c1 = player_collider)
	{
	
		/*App->fade->FadeToBlack((Module*)App->scene_space, (Module*)App->scene_intro);*/

	}
	

	
	

}
