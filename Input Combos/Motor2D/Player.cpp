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

	pugi::xml_document	config_file;
	pugi::xml_node* node = &App->LoadConfig(config_file); //todo: make a method to get the root without passing the xml_document
	node = &node->child("entities").child("player");

	//read animation from node
	for (pugi::xml_node animations = node->child("animations").child("animation"); animations && ret; animations = animations.next_sibling("animation"))
	{
		std::string tmp(animations.attribute("name").as_string());

		if (tmp == "idle")
			LoadAnimation(animations, &idle);
		else if (tmp == "forward")
			LoadAnimation(animations, &forward);
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

	current_state = PlayerState::ST_IDLE;
	
	if (dt > 0)
	{
		if (!key_entities_speed)
			SetEntitiesSpeed(dt);

		SetPlayerAnimationsSpeed(dt);
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		position.x += 2;
		this->current_state = PlayerState::ST_FORWARD;
	}else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		position.x -= 2;
		this->current_state = PlayerState::ST_BACKWARD;
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
		animation = &forward;
		break;
	case Player::ST_HADOKEN:
		break;
	case Player::ST_UNKNOWN:
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
	hadoken.speed = hadoken_vel * dt;;
}

void Player::SetEntitiesSpeed(float dt) 
{
	idle_vel = idle.speed;
	forward_vel = forward.speed;
	backward_vel = backward.speed;
	hadoken_vel = hadoken.speed;

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