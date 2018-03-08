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

#define PLAYER_SPEED 40.0f
#define JUMP_SPEED 40.0f
#define GRAVITY 60.0f


Player::Player(int x, int y) : Entity(x, y) {

	bool ret = true;

	
	animation = &right_idle;
	LOG("TIMER: %i",timer);
}

Player::~Player()
{
	LOG("Freeing the player");

	LOG("Unloading player sound fx");
	App->audio->UnLoadFx(player_jump_fx);
	App->audio->UnLoadFx(player_dead_fx);
	App->audio->UnLoadFx(player_life_reward_fx);
}

// Called each loop iteration
void Player::Update(float dt)
{
	if (player_appeared == false)
	{
		real_timer.Start();
		player_appeared = true;
		real_timer.SetStartTime(-time_implement_load);
		timer = real_timer.Read();
		LOG("TIMER: %i", timer);
	}

	timer = real_timer.Read();
	//LOG("timer: %i", timer);
	current_frame = animation->GetCurrentFrame();
	current_dt = dt;
	current_state = PlayerState::ST_UNKNOWN;

	if (dt > 0)
	{
		if (!key_entities_speed)
			SetEntitiesSpeed(dt);

		SetPlayerAnimationsSpeed(dt);
	}
	
	if (!isDead)
	{ //MOVEMENT / GRAVITY FUNCTIONALITY

		if (App->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN)
			god_mode = !god_mode;
		if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
		{
			god_mode_fly = !god_mode_fly;

			if (!god_mode_fly)
				god_mode = false;
		}
			

		if (god_mode_fly && !god_mode)
			god_mode = true;


		if (score % 10 == 0 && score != last_score && App->entities->GetPlayer()->p_lives != 6)
		{
			App->entities->GetPlayer()->p_lives++;
			App->audio->PlayFx(player_life_reward_fx);
		}

		last_score = score;

		if (!god_mode_fly)
		{

		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && !didDoubleJump)
		{
			if (!isJumping)
			{
				App->audio->PlayFx(player_jump_fx);
				isJumping = true;
			}
			else
			{
				App->audio->PlayFx(player_jump_fx);
				didDoubleJump = true;
				left_jump.Reset();
				right_jump.Reset();
			}
			jumpTimer = SDL_GetTicks();
		}
		
		
		if ((App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT) && PlayerCanShootRight())
		{
			if (currentTime > shoot_timer + 700) 
			{
				App->particles->AddParticle(App->particles->player_basic_shot_right, position.x + 5, position.y - 9, COLLIDER_PLAYER_BASIC_SHOT);
				shoot_timer = SDL_GetTicks();
			}
			SetPlayerStates(ST_SHOOT_RIGHT, LAST_ST_SHOOT_RIGHT);
		}

		if ((App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT) && PlayerCanShootLeft())
		{
			if (currentTime > shoot_timer + 700) 
			{
				App->particles->AddParticle(App->particles->player_basic_shot_left, position.x - 5, position.y - 9, COLLIDER_PLAYER_BASIC_SHOT);
				shoot_timer = SDL_GetTicks();
			}
			SetPlayerStates(ST_SHOOT_LEFT, LAST_ST_SHOOT_LEFT);
		}

		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			this->position.x += canGoRight();
			SetPlayerStates(ST_RUN_RIGHT, LAST_ST_RUN_RIGHT);
		}

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			this->position.x -= canGoLeft();
			SetPlayerStates(ST_RUN_LEFT, LAST_ST_RUN_LEFT);
		}

		bool isGettingHigh = false;

	
			if (currentTime <= jumpTimer + 500 && isJumping)
				isGettingHigh = true;

			if (!isGettingHigh)
			{
				if (float gravity = gravityHaveToWork())
				{
					this->position.y += gravity;
					isJumping = true;
				}
			}

			if (isJumping && isGettingHigh)
				this->position.y -= canGoUp();
		}
		else
		{
			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{
				SetPlayerStates(ST_IDLE_RIGHT, LAST_ST_IDLE_RIGHT);
				this->position.x += ceil(PLAYER_SPEED * current_dt);
			}
				
			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			{
				SetPlayerStates(ST_IDLE_LEFT, LAST_ST_IDLE_LEFT);
				this->position.x -= ceil(PLAYER_SPEED * current_dt);
			}
			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
				this->position.y -= ceil(PLAYER_SPEED * current_dt);
			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
				this->position.y += ceil(PLAYER_SPEED * current_dt);
			
		}

	}


	//SEARCH THE STATE AND SET THE ANIMATION
	SetPlayerAnimation(current_state, last_state);

	//DEAD ANIMATION WITH TIMER
	if (isDead && currentTime < deadTime + 1000)
	{
		if (last_state == LAST_ST_RUN_RIGHT)
			animation = &right_death_blink;
		else
			animation = &left_death_blink;
	}
	else if (isDead)
	{
		p_lives--;
		isDead = false;
		collider->type = COLLIDER_PLAYER;
		iPoint spawnPos = App->map->spawn;
		this->position.x = spawnPos.x;
		this->position.y = spawnPos.y;
	}

	// Draw everything --------------------------------------
	SDL_Rect r = animation->GetCurrentFrame();

	// Update player collider
	collider->SetPos(position.x, position.y - r.h);
	collider->rect.w = r.w;
	collider->rect.h = r.h;

	/*
	if (!App->render->Blit(graphics, (int)position.x, (int)position.y - r.h, &r)) {
	LOG("Cannot blit the texture in j1Player %s\n", SDL_GetError());
	}
	*/

	currentTime = SDL_GetTicks();
}

void Player::OnCollision(Collider* collider) {

	if (((collider->type == COLLIDER_ENEMY_BAT || collider->type == COLLIDER_ENEMY_SLIME) && !isDead) && !god_mode) {
		isDead = true;
		App->audio->PlayFx(player_dead_fx);
		deadTime = SDL_GetTicks();
	}
	else
	if (collider->type == COLLIDER_LVL_END)
	{
		if (!reachedEnd)
			reachedEnd = true;
	}
}

float Player::gravityHaveToWork()
{

	fPoint tmpPosLeft;
	tmpPosLeft.x = position.x;
	tmpPosLeft.y = position.y - 1;

	iPoint characterPosInTileWorldLeft = App->map->WorldToMap(tmpPosLeft.x, tmpPosLeft.y);

	fPoint tmpPosRight;
	tmpPosRight.x = position.x + collider->rect.w - 1;
	tmpPosRight.y = position.y - 1;

	iPoint characterPosInTileWorldRight = App->map->WorldToMap(tmpPosRight.x, tmpPosRight.y);

	characterPosInTileWorldLeft.y++;
	characterPosInTileWorldRight.y++;

	if ((App->map->collisionLayer->Get(characterPosInTileWorldLeft.x, characterPosInTileWorldLeft.y) == 596 || App->map->collisionLayer->Get(characterPosInTileWorldRight.x, characterPosInTileWorldRight.y) == 596) && !isDead) {
		if (god_mode) {
			position.x = App->map->MapToWorld(last_save_position.x, last_save_position.y).x;
			position.y = App->map->MapToWorld(last_save_position.x, last_save_position.y).y;
		}
		else {
			didDoubleJump = isJumping = false;
			left_jump.Reset();
			right_jump.Reset();
			jumpTimer = 0;
			isDead = true;
			App->audio->PlayFx(player_dead_fx);
			deadTime = SDL_GetTicks();


			characterPosInTileWorldLeft = App->map->MapToWorld(characterPosInTileWorldLeft.x, characterPosInTileWorldLeft.y);
			characterPosInTileWorldRight = App->map->MapToWorld(characterPosInTileWorldRight.x, characterPosInTileWorldRight.y);
			SDL_Rect tileColliderUp = { characterPosInTileWorldLeft.x,characterPosInTileWorldLeft.y, App->map->data.tile_width , App->map->data.tile_height };

			SDL_Rect tileColliderDown = { characterPosInTileWorldRight.x,characterPosInTileWorldRight.y, App->map->data.tile_width , App->map->data.tile_height };

			SDL_Rect player = { position.x, position.y - collider->rect.h, collider->rect.w, collider->rect.h };

			float distance_to_wall = DistanceToWall(tileColliderDown, player, DOWN);
			distance_to_wall *= -1;
			if (distance_to_wall == 0.0f)
				return 0.0f;
			else if (distance_to_wall >= ceil(GRAVITY * current_dt))
				return ceil(GRAVITY*current_dt);
			else if (distance_to_wall < ceil(GRAVITY*current_dt))
				return distance_to_wall;
		}
	}

	if (App->map->collisionLayer->Get(characterPosInTileWorldLeft.x, characterPosInTileWorldLeft.y) == 43 || App->map->collisionLayer->Get(characterPosInTileWorldRight.x, characterPosInTileWorldRight.y) == 43) {
		didDoubleJump = isJumping = false;
		left_jump.Reset();
		right_jump.Reset();

		characterPosInTileWorldLeft = App->map->MapToWorld(characterPosInTileWorldLeft.x, characterPosInTileWorldLeft.y);
		characterPosInTileWorldRight = App->map->MapToWorld(characterPosInTileWorldRight.x, characterPosInTileWorldRight.y);
		SDL_Rect tileColliderUp = { characterPosInTileWorldLeft.x,characterPosInTileWorldLeft.y, App->map->data.tile_width , App->map->data.tile_height };

		SDL_Rect tileColliderDown = { characterPosInTileWorldRight.x,characterPosInTileWorldRight.y, App->map->data.tile_width , App->map->data.tile_height };

		SDL_Rect player = { position.x, position.y - collider->rect.h, collider->rect.w, collider->rect.h };
		SDL_Rect res = { 0, 0, 0, 0 };

		float distance_to_wall = DistanceToWall(tileColliderDown, player, DOWN);
		distance_to_wall *= -1;

		fPoint tmpPosL;
		tmpPosL.x = position.x;
		tmpPosL.y = position.y - 1;
		iPoint characterLeft = App->map->WorldToMap(tmpPosL.x, tmpPosL.y);
		fPoint tmpPosR;
		tmpPosR.x = position.x + collider->rect.w - 1;
		tmpPosR.y = position.y - 1;

		(App->map->collisionLayer->Get(characterLeft.x, characterLeft.y + 1) == 43) ?
			last_save_position = App->map->WorldToMap(tmpPosL.x, tmpPosL.y)
			:
			last_save_position = App->map->WorldToMap(tmpPosR.x, tmpPosR.y);


		if (distance_to_wall == 0.0f)
			return 0.0f;
		else if (distance_to_wall >= ceil(GRAVITY * current_dt))
			return ceil(GRAVITY*current_dt);
		else if (distance_to_wall < ceil(GRAVITY*current_dt)) {
			return distance_to_wall;
		}
	}

	return ceil(GRAVITY*current_dt);
}

float Player::canGoLeft()
{
	bool ret = true;

	fPoint tmpPosUp;
	tmpPosUp.x = position.x;
	tmpPosUp.y = position.y - collider->rect.h;

	iPoint characterPosInTileWorldUp = App->map->WorldToMap(tmpPosUp.x, tmpPosUp.y);

	fPoint tmpPosDown;
	tmpPosDown.x = position.x;
	tmpPosDown.y = position.y - 1;

	iPoint characterPosInTileWorldDown = App->map->WorldToMap(tmpPosDown.x, tmpPosDown.y);

	characterPosInTileWorldUp.x--;
	characterPosInTileWorldDown.x--;
	if (App->map->collisionLayer->Get(characterPosInTileWorldUp.x, characterPosInTileWorldUp.y) != 0 || App->map->collisionLayer->Get(characterPosInTileWorldDown.x, characterPosInTileWorldDown.y) != 0) {

		//characterPosInTileWorldUp = App->map->MapToWorld(characterPosInTileWorldUp.x, characterPosInTileWorldUp.y);
		characterPosInTileWorldDown = App->map->MapToWorld(characterPosInTileWorldDown.x, characterPosInTileWorldDown.y);
		//SDL_Rect tileColliderUp = { characterPosInTileWorldUp.x,characterPosInTileWorldUp.y, App->map->data.tile_width , App->map->data.tile_height };

		SDL_Rect tileColliderDown = { characterPosInTileWorldDown.x,characterPosInTileWorldDown.y, App->map->data.tile_width , App->map->data.tile_height };

		SDL_Rect player = { position.x, position.y - collider->rect.h, collider->rect.w, collider->rect.h };


		float distance_to_wall = DistanceToWall(tileColliderDown, player, LEFT);
		distance_to_wall *= -1;
		if (distance_to_wall == 0.0f)
			return 0.0f;
		else if (distance_to_wall >= ceil(PLAYER_SPEED * current_dt))
			return ceil(PLAYER_SPEED*current_dt);
		else if (distance_to_wall < ceil(PLAYER_SPEED*current_dt))
			return distance_to_wall;

	}

	return ceil(PLAYER_SPEED*current_dt);
}

float Player::canGoUp()
{
	bool ret = true;

	fPoint tmpPosLeft;
	tmpPosLeft.x = position.x;
	tmpPosLeft.y = position.y - collider->rect.h;

	iPoint characterPosInTileWorldLeft = App->map->WorldToMap(tmpPosLeft.x, tmpPosLeft.y);

	fPoint tmpPosRight;
	tmpPosRight.x = position.x + collider->rect.w - 1;
	tmpPosRight.y = position.y - collider->rect.h;

	iPoint characterPosInTileWorldRight = App->map->WorldToMap(tmpPosRight.x, tmpPosRight.y);

	characterPosInTileWorldLeft.y--;
	characterPosInTileWorldRight.y--;

	if (App->map->collisionLayer->Get(characterPosInTileWorldLeft.x, characterPosInTileWorldLeft.y) != 0 || App->map->collisionLayer->Get(characterPosInTileWorldRight.x, characterPosInTileWorldRight.y) != 0) {

		//isJumping = false;

		characterPosInTileWorldRight = App->map->MapToWorld(characterPosInTileWorldRight.x, characterPosInTileWorldRight.y);

		SDL_Rect tileColliderDown = { characterPosInTileWorldRight.x,characterPosInTileWorldRight.y + App->map->data.tile_height, App->map->data.tile_width , App->map->data.tile_height };

		SDL_Rect player = { position.x, position.y - collider->rect.h, collider->rect.w, collider->rect.h };

		float distance_to_wall = DistanceToWall(tileColliderDown, player, UP);
		//distance_to_wall *= -1;
		if (distance_to_wall == 0.0f) {
			isJumping = false;
			jumpTimer = 0;
			return 0.0f;
		}
		else if (distance_to_wall >= ceil(JUMP_SPEED * current_dt))
			return ceil(JUMP_SPEED*current_dt);
		else if (distance_to_wall < ceil(JUMP_SPEED*current_dt)) {
			return distance_to_wall;
		}
	}
	return ceil(JUMP_SPEED*current_dt);
}

bool Player::PlayerCanShootRight()
{
	return (last_state == PlayerLastState::LAST_ST_RUN_RIGHT
			|| last_state == PlayerLastState::LAST_ST_IDLE_RIGHT
			|| last_state == PlayerLastState::LAST_ST_SHOOT_RIGHT);
}

bool Player::PlayerCanShootLeft()
{
	return (last_state == PlayerLastState::LAST_ST_RUN_LEFT
			|| last_state == PlayerLastState::LAST_ST_IDLE_LEFT
			|| last_state == PlayerLastState::LAST_ST_SHOOT_LEFT);
}

float Player::canGoRight()
{
	fPoint tmpPosUp;
	tmpPosUp.x = position.x + collider->rect.w - 1;
	tmpPosUp.y = position.y - collider->rect.h;

	iPoint characterPosInTileWorldUp = App->map->WorldToMap(tmpPosUp.x, tmpPosUp.y);

	fPoint tmpPosDown;
	tmpPosDown.x = position.x + collider->rect.w - 1;
	tmpPosDown.y = position.y - 1;

	iPoint characterPosInTileWorldDown = App->map->WorldToMap(tmpPosDown.x, tmpPosDown.y);

	characterPosInTileWorldUp.x++;
	characterPosInTileWorldDown.x++;
	if (App->map->collisionLayer->Get(characterPosInTileWorldUp.x, characterPosInTileWorldUp.y) != 0 || App->map->collisionLayer->Get(characterPosInTileWorldDown.x, characterPosInTileWorldDown.y) != 0) {

		characterPosInTileWorldDown = App->map->MapToWorld(characterPosInTileWorldDown.x, characterPosInTileWorldDown.y);
		SDL_Rect tileColliderDown = { characterPosInTileWorldDown.x,characterPosInTileWorldDown.y, App->map->data.tile_width , App->map->data.tile_height };
		SDL_Rect player = { position.x, position.y - collider->rect.h, collider->rect.w, collider->rect.h };

		float distance_to_wall = DistanceToWall(tileColliderDown, player, RIGHT);
		distance_to_wall *= -1;
		if (distance_to_wall == 0.0f)
			return 0.0f;
		else if (distance_to_wall >= ceil(PLAYER_SPEED * current_dt))
			return ceil(PLAYER_SPEED*current_dt);
		else if (distance_to_wall < ceil(PLAYER_SPEED*current_dt))
			return distance_to_wall;

	}

	return ceil(PLAYER_SPEED*current_dt);
}

float Player::DistanceToWall(SDL_Rect wall, SDL_Rect player, Direction direction)
{
	switch (direction)
	{
	case Direction::RIGHT:
		return player.x + player.w - wall.x;
		break;
	case Direction::LEFT:
		return wall.x + wall.w - player.x;
		break;
	case Direction::UP:
		return player.y - wall.y;
		break;
	case Direction::DOWN:
		return player.y + player.h - wall.y;
		break;
	case Direction::NO_DIR:
	default:
		LOG("YOU ARE DOING IT WRONG!");
		break;
	}
}


void Player::SetPlayerAnimation(PlayerState current_state, PlayerLastState last_state)
{
	switch (current_state)
	{
	case Player::ST_UNKNOWN:
		switch (last_state)
		{
		case Player::LAST_ST_UNKNOWN:
			break;
		case Player::LAST_ST_IDLE_RIGHT:
			break;
		case Player::LAST_ST_IDLE_LEFT:
			break;
		case Player::LAST_ST_RUN_RIGHT:
			if (isJumping)
				animation = &right_jump;
			else
				animation = &right_idle;
			break;
		case Player::LAST_ST_RUN_LEFT:
			if (isJumping)
				animation = &left_jump;
			else
				animation = &left_idle;
			break;
		case Player::LAST_ST_SHOOT_RIGHT:
			if (isJumping)
				animation = &right_jump;
			else
				animation = &right_idle;
			break;
		case Player::LAST_ST_SHOOT_LEFT:
			if (isJumping)
				animation = &left_jump;
			else
				animation = &left_idle;
			break;
		default:
			break;
		}
		break;
	case Player::ST_IDLE_RIGHT:
		break;
	case Player::ST_IDLE_LEFT:
		break;
	case Player::ST_RUN_RIGHT:
		if (isJumping)
			animation = &right_jump;
		else
			animation = &right_run;
		break;
	case Player::ST_RUN_LEFT:
		if (isJumping)
			animation = &left_jump;
		else
			animation = &left_run;
		break;
	case Player::ST_SHOOT_RIGHT:
		if (isJumping)
			animation = &right_jump;
		else
			animation = &right_shoot;
		break;
	case Player::ST_SHOOT_LEFT:
		if (isJumping)
			animation = &left_jump;
		else
			animation = &left_shoot;
		break;
	default:
		break;
	}
}

void Player::SetPlayerStates(PlayerState current_state, PlayerLastState last_state)
{
	this->current_state = current_state;
	this->last_state = last_state;
}

void Player::SetPlayerAnimationsSpeed(float dt)
{
	right_idle.speed = right_idle_vel * dt;
	left_idle.speed = left_idle_vel * dt;
	right_run.speed = right_run_vel * dt;;
	left_run.speed = left_run_vel * dt;;
	right_jump.speed = right_jump_vel * dt;
	left_jump.speed = left_jump_vel * dt;
	right_death_blink.speed = right_death_blink_vel * dt;
	left_death_blink.speed = left_death_blink_vel * dt;
	right_shoot.speed = right_shoot_vel * dt;
	left_shoot.speed = left_shoot_vel * dt;
}

bool Player::Load(pugi::xml_node& load)
{
	bool ret = true;

	if (!load.child("position").empty())
	{
		position_implement_load.x = load.child("position").attribute("x").as_float();
		position_implement_load.y = load.child("position").attribute("y").as_float() - 2.0f;
	}

	if (!load.child("info").empty()) {
		lives_implement_load = load.child("info").attribute("lives").as_int();
		score_implement_load = load.child("info").attribute("score").as_int();
		time_implement_load = load.child("info").attribute("time").as_int();
	}

	if (App->fadeToBlack->FadeIsOver())
		ImplementLoad();
	else {
		p_lives = lives_implement_load;
		score = score_implement_load;
		position.x = position_implement_load.x;
		position.y = position_implement_load.y;

		real_timer.Start();
		player_appeared = true;
		real_timer.SetStartTime(-time_implement_load);
		timer = real_timer.Read();
		LOG("TIMER: %i", timer);
	}

	return ret;
}

void Player::ImplementLoad()
{
	p_lives = lives_implement_load;
	score = score_implement_load;
	position.x = position_implement_load.x;
	position.y = position_implement_load.y;
	
	real_timer.Start();
	player_appeared = true;
	real_timer.SetStartTime(-time_implement_load);
	timer = real_timer.Read();
	LOG("TIMER: %i", timer);
}

bool Player::Save(pugi::xml_node& save) const
{
	bool ret = true;

	if (save.child("position").empty())
	{
		pugi::xml_node&  tmpsave = save.append_child("position");
		tmpsave.append_attribute("x").set_value(position.x);
		tmpsave.append_attribute("y").set_value(position.y);
	}
	else
	{
		save.child("position").attribute("x").set_value(position.x);
		save.child("position").attribute("y").set_value(position.y);
	}

	if (save.child("info").empty())
	{
		pugi::xml_node&  tmpsave = save.append_child("info");
		tmpsave.append_attribute("lives").set_value(p_lives);
		tmpsave.append_attribute("score").set_value(score);
		tmpsave.append_attribute("time").set_value(timer);
	}
	else
	{
		save.child("info").attribute("lives").set_value(p_lives);
		save.child("info").attribute("score").set_value(score);
		save.child("info").attribute("time").set_value(timer);
	}

	return ret;
}

void Player::ResetData()
{
	lives_implement_load = 0;
	score_implement_load = 0;
	time_implement_load = 0;
}

void Player::SetEntitiesSpeed(float dt) 
{
	right_idle_vel = right_idle.speed;
	left_idle_vel = left_idle.speed;
	right_jump_vel = right_jump.speed;
	left_jump_vel = left_jump.speed;
	right_run_vel = right_run.speed;
	left_run_vel = left_run.speed;
	right_death_blink_vel = right_death_blink.speed;
	left_death_blink_vel = left_death_blink.speed;

	key_entities_speed = true;
}