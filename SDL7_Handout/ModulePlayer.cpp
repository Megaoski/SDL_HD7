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
	/*right.loop = false;*/


	punch.SetUp(216, 16, 50, 52, 3, 3, "0,1,2");
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
	position.y = 134;
	
	jump = false;
	

	//direction = { -1,0 }; needs to be implemented
	
	
	collider_offset.x = 7;
	collider_offset.y = 2;
	player_collider = App->collision->AddCollider({0, 0, 37, 50}, COLLIDER_PLAYER, this);

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

		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && App->player->position.x >= -7)
		{
			position.x -= speed;
			current_animation = &left;			
			state = LEFT;
		}

		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_UP) { //con esto se evita que se quede calada la animacion al soltar la tecla
			current_animation = &idle;
			state = IDLE;
		}

		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && App->player->position.x <= 342)
		{
			position.x += speed;
			current_animation = &right;
			state = RIGHT;
		}

		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_UP)
		{
			current_animation = &idle;
			state = IDLE;
		}

		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
		{
			current_animation = &down;
			state = CROUCH;
		}

		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_UP)
		{
			current_animation = &idle;
			state = IDLE;
		}

		break;

	case LEFT:

		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && App->player->position.x >= -7)
		{
			position.x -= speed;
			current_animation = &left;
			state = LEFT;
		}

		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_UP) {
			current_animation = &idle;
			state = IDLE;
		}

		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && App->player->position.x <= 342)
		{
			position.x += speed;
			current_animation = &right;
			state = RIGHT;
		}

		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_UP) {
			current_animation = &idle;
			state = IDLE;
		}

		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
		{
			current_animation = &down;
			state = CROUCH;
		}

		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_UP) {
			current_animation = &idle;
			state = IDLE;
		}
		break;
	case RIGHT:

		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && App->player->position.x >= -7)
		{
			position.x -= speed;
			current_animation = &left;
			state = LEFT;
		}

		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_UP) {
			current_animation = &idle;
			state = IDLE;
		}

		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && App->player->position.x <= 342)
		{
			position.x += speed;
			current_animation = &right;
			state = RIGHT;
		}

		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_UP) {
			current_animation = &idle;
			state = IDLE;
		}

		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
		{
			current_animation = &down;
			state = CROUCH;
		}

		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_UP) {
			current_animation = &idle;
			state = IDLE;
		}
		break;
	case CROUCH:

		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && App->player->position.x >= -7)
		{
			current_animation = &down;
			state = CROUCH;
		}

		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_UP) { // MIGH NOT NEED THIS HERE
			current_animation = &idle;
			state = IDLE;
		}

		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && App->player->position.x <= 342)
		{
			current_animation = &down;
			state = CROUCH;
		}

		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_UP) {
			current_animation = &idle;
			state = IDLE;
		}

		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
		{
			current_animation = &down;
			state = CROUCH;
		}

		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_UP) {
			current_animation = &idle;
			state = IDLE;
		}
		break;


	} //finish switch

	



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

//bool ModulePlayer::isGrounded()
//{
//	if (position.y == 134)
//		return true;
//	else
//		return false;
//}