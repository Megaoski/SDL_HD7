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
#include "SDL/include/SDL_timer.h"






ModulePlayer::ModulePlayer()
{
	idle.SetUp(6, 16, 50, 52, 4, 4, "0,1,2,3");
	idle.speed = 0.1f;



	up.SetUp(6, 16, 50, 52, 4, 4, "0,1,2,3");
	up.speed = 0.1f;



	down.SetUp(216, 16, 50, 52, 3, 3, "0,1,2");
	down.speed = 0.1f;
	down.loop = false;


	left.SetUp(435, 16, 50, 52, 2, 2, "1");
	left.speed = 0.1f;
	

	right.SetUp(543, 16, 40, 52, 6, 6, "0,1,2,3,4,5");
	right.speed = 0.1f;
	


	punch.SetUp(0, 70, 60, 52, 2, 2, "1");
	punch.speed = 0.1f;
	punch.loop = false;
	
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("rtype/sprites-finales.png");


	
	original_position.x = 150;
	original_position.y = 134;
	current_position.x = 150;
	current_position.y = 134;
	
	
	
	


	
	
	collider_offset.x = 18;
	collider_offset.y = 10;
	player_collider = App->collision->AddCollider({0, 10, 15, 40}, COLLIDER_PLAYER, this);

	crouch_collider_offset.x = 18;
	crouch_collider_offset.y = 30 ;
	
	
	current_animation = &idle;
	state = IDLE;
	
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
	

	switch (state) {

	case IDLE:
		player_collider->SetPos(current_position.x + collider_offset.x, current_position.y + collider_offset.y);//DEFAULT COLLIDER FOR IDLE
		current_animation = &idle;
		


		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && App->player->current_position.x >= -7)
		{
			current_position.x -= speed;
			current_animation = &left;
			state = LEFT;
		}

		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && App->player->current_position.x <= 342)
		{
			current_position.x += speed;
			current_animation = &right;
			state = RIGHT;
		}

		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
		{
			App->collision->ColliderSize(player_collider, { 0, 0, 15, 20 });
			player_collider->SetPos(current_position.x + crouch_collider_offset.x, current_position.y + crouch_collider_offset.y);

			current_animation = &down;
			state = CROUCH;
		}


		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
		{

			state = FIGHT;


		}

		break;

	case LEFT:

		player_collider->SetPos(current_position.x + collider_offset.x, current_position.y + collider_offset.y);

		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && App->player->current_position.x >= -7)
		{
			current_position.x -= speed;
			current_animation = &left;
			state = LEFT;
		}

		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_UP) {
			current_animation = &idle;
			state = IDLE;
		}

		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && App->player->current_position.x <= 342)
		{
			current_position.x += speed;
			current_animation = &right;
			state = RIGHT;
		}

		
		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
		{
			App->collision->ColliderSize(player_collider, { 0, 0, 15, 20 });
			player_collider->SetPos(current_position.x + crouch_collider_offset.x, current_position.y + crouch_collider_offset.y);
			current_animation = &down;
			state = CROUCH;
		}

		
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {



			state = FIGHT;
		}

		break;
	case RIGHT:

		player_collider->SetPos(current_position.x + collider_offset.x, current_position.y + collider_offset.y);

		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && App->player->current_position.x >= -7)
		{
			current_position.x -= speed;
			current_animation = &left;
			state = LEFT;
		}

		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && App->player->current_position.x <= 342)
		{
			current_position.x += speed;
			current_animation = &right;
			state = RIGHT;
		}

		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_UP) {
			current_animation = &idle;
			state = IDLE;
		}

		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
		{
			App->collision->ColliderSize(player_collider, { 0, 0, 15, 20 });
			player_collider->SetPos(current_position.x + crouch_collider_offset.x, current_position.y + crouch_collider_offset.y);
			current_animation = &down;
			state = CROUCH;
		}

		
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {



			state = FIGHT;
		}

		break;
	case CROUCH:

		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && App->player->current_position.x >= -7)
		{
			current_animation = &down;
			state = CROUCH;
		}

		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && App->player->current_position.x <= 342)
		{
			current_animation = &down;
			state = CROUCH;
		}

		
		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
		{

			current_animation = &down;
			state = CROUCH;
		}

		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_UP) {
			App->collision->ColliderSize(player_collider, { 0, 0, 15, 40 });
			player_collider->SetPos(current_position.x + collider_offset.x, current_position.y + collider_offset.y);
			current_animation = &idle;
			state = IDLE;
		}

		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {



			state = FIGHT;
		}

		break;
	case FIGHT:

		current_animation = &punch;

		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_UP)
		{
			state = IDLE;
		}

		break;

	}
			
	App->render->Blit(graphics, current_position.x, current_position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}

	
 
void ModulePlayer::OnCollision( Collider* c1, Collider* c2)
{
	
	if (c1 = player_collider)
	{
	
		current_position.y = 134;

	}
	

	
	

}

