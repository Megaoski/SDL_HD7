#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

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
	iPoint position;
	
	void OnCollision(Collider* c1, Collider* c2);

	Collider* player_collider;
	iPoint collider_offset;
	bool jump;
	//iPoint direction = { 0,1 }; still needs to be implemented
private:
	enum player_state {
		OFF = 0,
		DEAD,
		IDLE,
		LEFT,
		RIGHT,
		UP,
		CROUCH
	};

	player_state state;
	
};

#endif