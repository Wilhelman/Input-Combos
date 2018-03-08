#ifndef __j1Player_H__
#define __j1Player_H__

#include "ctAnimation.h"
#include "ctPoint.h"
#include "Entity.h"

class j1Timer;
struct SDL_Texture;

class Player : public Entity
{
	enum PlayerState
	{
		ST_IDLE,
		ST_HADOKEN,

		ST_UNKNOWN
	};

public:

	SDL_Rect current_frame = { 0,0,0,0 };

private:

	float current_dt = 0.0f;
	PlayerState current_state = PlayerState::ST_IDLE;

	//playerSoundEffects
	uint hadouken_fx = 0u;

	//anims
	ctAnimation idle = ctAnimation();
	ctAnimation forward = ctAnimation();
	ctAnimation backward = ctAnimation();
	ctAnimation hadouken = ctAnimation();

	//anims speed
	uint idle = 0u, hadouken = 0u;


	iPoint position;

private:

public:

	Player(int x, int y);
	~Player();

	void Update(float dt);
};

#endif