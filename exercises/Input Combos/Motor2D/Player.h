#ifndef __j1Player_H__
#define __j1Player_H__

#include "ctAnimation.h"
#include "ctPoint.h"
#include "Entity.h"

class Player : public Entity
{
	enum PlayerState
	{
		ST_IDLE,
		ST_FORWARD,
		ST_BACKWARD,
		ST_SHORYUKEN,
		ST_TATSUMAKI,

		ST_UNKNOWN
	};

public:

	//player's current frame (entity)
	SDL_Rect current_frame = { 0,0,0,0 };

	void OnComboCompleted(ComboType type);

private:

	//player state
	PlayerState current_state = PlayerState::ST_IDLE;

	//animations
	ctAnimation idle = ctAnimation();
	ctAnimation forward = ctAnimation();
	ctAnimation backward = ctAnimation();
	ctAnimation shoryuken = ctAnimation();
	ctAnimation tatsumaki = ctAnimation();

	//animations velocity
	uint idle_vel = 0u, forward_vel = 0u, backward_vel = 0u, shoryuken_vel = 0u, tatsumaki_vel = 0u;

	//action examples helpers
	bool performing_shoryuken = false;
	bool performing_tatsumaki = false;

private:

	void SetPlayerAnimationsSpeed(float dt);
	void SetEntitiesSpeed(float dt);
	void LoadAnimation(pugi::xml_node animation_node, ctAnimation* animation);

public:

	Player(int x, int y, EntityType type);
	~Player();

	void Update(float dt);
};

#endif