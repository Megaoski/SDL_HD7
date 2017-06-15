#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "SDL/include/SDL.h"

#define COOLDOWN 3000

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation up;
	Animation down;
	Animation left;
	Animation right;
	Animation punch;

	iPoint original_position;
	iPoint current_position;
	/*void jumping();
	float gravity;
	float kilos;*/
	void OnCollision(Collider* c1, Collider* c2);

	Collider* player_collider = nullptr;
	iPoint collider_offset;
	iPoint crouch_collider_offset;
	uint sdl_clock;
	uint timer;
	bool yahaclickao;
	bool salimos;
	void Punching();

	
	//iPoint direction = { 0,1 }; still needs to be implemented
private:
	enum player_state {
		OFF = 0,
		DEAD,
		IDLE,
		LEFT,
		RIGHT,
		UP,
		CROUCH,
		FIGHT
	};

	player_state state;
	
};

#endif