#include "ctDefs.h"
#include "ctLog.h"
#include "ctApp.h"
#include "ctInput.h"
#include "ctRender.h"
#include "ctTextures.h"
#include "ctFadeToBlack.h"
#include "ctAudio.h"
//#include "ctParticles.h"
#include "ctEntities.h"
#include "ctTimer.h"

#include "Player.h"


Player::Player(int x, int y, EntityType type) : Entity(x, y, type) {

	bool ret = true;

}

Player::~Player()
{
	LOG("Freeing the player");

}

// Called each loop iteration
void Player::Update(float dt)
{

	if (dt > 0)
	{
		if (!key_entities_speed)
			SetEntitiesSpeed(dt);

		SetPlayerAnimationsSpeed(dt);
	}
}

void Player::SetPlayerAnimationsSpeed(float dt)
{
	idle.speed = idle_vel * dt;
	forward.speed = forward_vel * dt;
	hadoken.speed = hadoken_vel * dt;;
}

void Player::SetEntitiesSpeed(float dt) 
{
	idle_vel = idle.speed;
	forward_vel = forward.speed;
	hadoken_vel = hadoken.speed;

	key_entities_speed = true;
}