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

#include "Combo.h"

#include "Player.h"


Player::Player(int x, int y, EntityType type) : Entity(x, y, type) {

	bool ret = true;

	pugi::xml_document	config_file;
	pugi::xml_node* node = &App->LoadConfig(config_file);
	node = &node->child("entities").child("player");

	for (pugi::xml_node animations = node->child("animations").child("animation"); animations && ret; animations = animations.next_sibling("animation"))
	{
		std::string tmp(animations.attribute("name").as_string());

		if (tmp == "idle")
			LoadAnimation(animations, &idle);
		else if (tmp == "forward")
			LoadAnimation(animations, &forward);
		else if (tmp == "backward")
			LoadAnimation(animations, &backward);
		else if (tmp == "shoryuken")
			LoadAnimation(animations, &shoryuken);
		else if (tmp == "tatsumaki")
			LoadAnimation(animations, &tatsumaki);
	}

	animation = &idle;

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

	if (performing_shoryuken) {
		current_state = PlayerState::ST_SHORYUKEN;
		if (shoryuken.GetCurrentFrame().x == shoryuken.frames[5].x) {
			performing_shoryuken = false;
			current_state = PlayerState::ST_IDLE;
		}
	}
	else if (performing_tatsumaki) {
		current_state = PlayerState::ST_TATSUMAKI;
		if (tatsumaki.GetCurrentFrame().x == tatsumaki.frames[10].x) {
			performing_tatsumaki = false;
			current_state = PlayerState::ST_IDLE;
		}
	}
	else {
		current_state = PlayerState::ST_IDLE;

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT || App->input->gamepad.CROSS_RIGHT == GAMEPAD_STATE::PAD_BUTTON_REPEAT) {
			if (position.x < 650)
				position.x += 2;
			this->current_state = PlayerState::ST_FORWARD;
		}
		else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT || App->input->gamepad.CROSS_LEFT == GAMEPAD_STATE::PAD_BUTTON_REPEAT) {
			if(position.x > 400)
				position.x -= 2;
			this->current_state = PlayerState::ST_BACKWARD;
		}
	}

	switch (current_state)
	{
	case Player::ST_IDLE:
		animation = &idle;
		break;
	case Player::ST_FORWARD:
		animation = &forward;
		break;
	case Player::ST_BACKWARD:
		animation = &backward;
		break;
	case Player::ST_SHORYUKEN:
		animation = &shoryuken;
		break;
	case Player::ST_TATSUMAKI:
		animation = &tatsumaki;
		break;
	case Player::ST_UNKNOWN:
		break;
	default:
		break;
	}
}

void Player::OnComboCompleted(ComboType type) {
	switch (type)
	{
	case SHORYUKEN:
		//LOG("SHORYUKEN!");
		shoryuken.Reset();
		performing_shoryuken = true;
		break;
	case TATSUMAKI:
		//LOG("TATSUMAKI!");
		tatsumaki.Reset();
		performing_tatsumaki = true;
		break;
	default:
		break;
	}
}

void Player::SetPlayerAnimationsSpeed(float dt)
{
	idle.speed = idle_vel * dt;
	forward.speed = forward_vel * dt;
	backward.speed = backward_vel * dt;
	shoryuken.speed = shoryuken_vel * dt;
	tatsumaki.speed = tatsumaki_vel * dt;
}

void Player::SetEntitiesSpeed(float dt) 
{
	idle_vel = idle.speed;
	forward_vel = forward.speed;
	backward_vel = backward.speed;
	shoryuken_vel = shoryuken.speed;
	tatsumaki_vel = tatsumaki.speed;

	key_entities_speed = true;
}

void Player::LoadAnimation(pugi::xml_node animation_node, ctAnimation* animation)
{
	bool ret = true;

	for (pugi::xml_node frame = animation_node.child("frame"); frame && ret; frame = frame.next_sibling("frame"))
		animation->PushBack({ frame.attribute("x").as_int() , frame.attribute("y").as_int(), frame.attribute("width").as_int(), frame.attribute("height").as_int() });

	animation->speed = animation_node.attribute("speed").as_float();
	animation->loop = animation_node.attribute("loop").as_bool();
}