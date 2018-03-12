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
		ST_HADOKEN,

		ST_UNKNOWN
	};

public:

	//player's current frame (entity)
	SDL_Rect current_frame = { 0,0,0,0 };

private:

	//player state
	PlayerState current_state = PlayerState::ST_IDLE;

	//playerSoundEffects
	uint hadouken_fx = 0u;

	//animations
	ctAnimation idle = ctAnimation();
	ctAnimation forward = ctAnimation();
	ctAnimation backward = ctAnimation();
	ctAnimation hadoken = ctAnimation();

	//animations velocity
	uint idle_vel = 0u, forward_vel = 0u, hadoken_vel = 0u;

private:

	void SetPlayerAnimationsSpeed(float dt);
	void SetEntitiesSpeed(float dt);

public:

	Player(int x, int y, EntityType type);
	~Player();

	void Update(float dt);
};

#endif