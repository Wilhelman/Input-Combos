#include "ctDefs.h"
#include "ctLog.h"
#include "ctApp.h"
#include "ctInput.h"
#include "ctTextures.h"
#include "ctAudio.h"
#include "ctRender.h"
#include "ctWindow.h"
#include "ctEntities.h"
#include "ctInputCombo.h"
#include "InputEvent.h"

#include "ctKenStageScene.h"

#include "ctFadeToBlack.h"

#include <list>



ctKenStageScene::ctKenStageScene() : ctModule()
{
	name = "ken_stage";
}

// Destructor
ctKenStageScene::~ctKenStageScene()
{}

// Called before render is available

bool ctKenStageScene::Awake(pugi::xml_node& conf)
{
	LOG("Loading KEN STAGE");
	bool ret = true;

	atlas_name = conf.child("spritesheetSource").attribute("name").as_string();

	pugi::xml_node* node = &conf.child("spritesheetSource");

	//read animations from node
	for (pugi::xml_node animations = node->child("animations").child("animation"); animations && ret; animations = animations.next_sibling("animation"))
	{
		std::string tmp(animations.attribute("name").as_string());

		if (tmp == "flag")
			LoadAnimation(animations, &flag);
		else if (tmp == "girl")
			LoadAnimation(animations, &girl);
		else if (tmp == "two_guys")
			LoadAnimation(animations, &two_guys);
		else if (tmp == "green_guy")
			LoadAnimation(animations, &green_guy);
		else if (tmp == "blue_guy")
			LoadAnimation(animations, &blue_guy);
		else if (tmp == "fedora_guy")
			LoadAnimation(animations, &fedora_guy);
		else if (tmp == "pink_guy")
			LoadAnimation(animations, &pink_guy);

	}

	//read rects from node
	for (pugi::xml_node rects = node->child("rects").child("rect"); rects && ret; rects = rects.next_sibling("rect"))
	{
		std::string tmp(rects.attribute("name").as_string());

		if (tmp == "ground")
			LoadRect(rects, &ground);
		else if (tmp == "foreground")
			LoadRect(rects, &foreground);
		else if (tmp == "background")
			LoadRect(rects, &background);
	}

	return ret;
}

// Called before the first frame
bool ctKenStageScene::Start()
{
	bool ret = true;

	LOG("KEN STAGE start!");

	if (!App->audio->PlayMusic("audio/music/ken.ogg")) {
		ret = false;
		LOG("Error playing music in ctKenStageScene Start");
	}

	atlas_tex = App->tex->Load(atlas_name.c_str());
	if (atlas_tex == nullptr)
		ret = false;

	App->entities->SpawnEntity(450, 210, PLAYER);

	if (App->input_combo->GetComboListSize() > 0)
		App->gui->AddUILabel(400, 10, "TODO 3 - Combos charged correctly!", { 0,255,0,255 }, nullptr);
	else
		App->gui->AddUILabel(400, 10, "TODO 3 - Combos not found!", { 255,0,0,255 }, nullptr);

	return ret;
}

// Called each loop iteration
bool ctKenStageScene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool ctKenStageScene::Update(float dt)
{

	if (dt > 0)
	{
		if (!key_speed)
			SetEntitiesSpeed(dt);

		SetSceneAnimationsSpeed(dt);
	}

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		this->quit_pressed = true;

	// Calculate boat Y position -----------------------------
	if (foreground_pos < -6.0f)
		forward_foreground = false;
	else if (foreground_pos > 0.0f)
		forward_foreground = true;

	if (forward_foreground)
		foreground_pos -= 0.02f;
	else
		foreground_pos += 0.02f;
	
	// Draw everything --------------------------------------
	App->render->Blit(atlas_tex, 0, 0, &background, 0.75f); // sea and sky
	App->render->Blit(atlas_tex, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation
	App->render->Blit(atlas_tex, 0, (int)foreground_pos, &foreground, 0.92f);// ship
	App->render->Blit(atlas_tex, 192, 104 + (int)foreground_pos, &(girl.GetCurrentFrame()), 0.92f); // girl animation
	App->render->Blit(atlas_tex, 128, 96 + (int)foreground_pos, &(two_guys.GetCurrentFrame()), 0.92f); // two_guys animation
	App->render->Blit(atlas_tex, 224, 104 + (int)foreground_pos, &(green_guy.GetCurrentFrame()), 0.92f); // green_guy animation
	App->render->Blit(atlas_tex, 288, 96 + (int)foreground_pos, &(blue_guy.GetCurrentFrame()), 0.92f); // blue_guy animation
	App->render->Blit(atlas_tex, 86, 24 + (int)foreground_pos, &(fedora_guy.GetCurrentFrame()), 0.92f); // fedora_guy animation
	App->render->Blit(atlas_tex, 130, 24 + (int)foreground_pos, &(pink_guy.GetCurrentFrame()), 0.92f); // pink_guy animation
	App->render->Blit(atlas_tex, 0, 170, &ground); //ground

	list<InputEvent*> tmp_chain = App->input_combo->GetEventChain();

	list<InputEvent*>::const_iterator it = tmp_chain.begin();

	int x_pos = 50;
	int y_pos = App->render->camera.y + App->render->camera.h - 22;

	while (it != tmp_chain.end()) {

		EventType tmp_type = (*it)->GetType();

		switch (tmp_type)
		{
		case RIGHT:
			App->render->DrawLine(x_pos, y_pos + 15, x_pos + 30, y_pos + 15, 0, 255, 0, 255, false);
			App->render->DrawLine(x_pos + 30, y_pos + 15, x_pos + 15, y_pos + 30, 0, 255, 0, 255, false);
			App->render->DrawLine(x_pos + 30, y_pos + 15, x_pos + 15, y_pos, 0, 255, 0, 255, false);
			break;
		case LEFT:
			App->render->DrawLine(x_pos, y_pos + 15, x_pos + 30, y_pos + 15, 0, 255, 0, 255, false);
			App->render->DrawLine(x_pos, y_pos + 15, x_pos + 15, y_pos+30, 0, 255, 0, 255, false);
			App->render->DrawLine(x_pos, y_pos + 15, x_pos + 15, y_pos, 0, 255, 0, 255, false);
			break;
		case UP:
			App->render->DrawLine(x_pos + 15, y_pos, x_pos + 15, y_pos + 30, 0, 255, 0, 255, false);
			App->render->DrawLine(x_pos, y_pos + 15, x_pos + 15, y_pos, 0, 255, 0, 255, false);
			App->render->DrawLine(x_pos + 30, y_pos + 15, x_pos + 15, y_pos, 0, 255, 0, 255, false);
			break;
		case DOWN:
			App->render->DrawLine(x_pos + 15, y_pos, x_pos + 15, y_pos + 30, 0, 255, 0, 255, false);
			App->render->DrawLine(x_pos, y_pos + 15, x_pos + 15, y_pos + 30, 0, 255, 0, 255, false);
			App->render->DrawLine(x_pos+30, y_pos + 15, x_pos + 15, y_pos + 30, 0, 255, 0, 255, false);
			break;
		case PUNCH:
			App->render->DrawQuad({ x_pos,y_pos,30,30 }, 255, 0, 0, 255, false, false);
			break;
		case KICK:
			App->render->DrawCircle(x_pos + 15, y_pos + 15, 15, 0, 0, 255, 255);
			break;
		case NO_EVENT_TYPE:
			break;
		default:
			break;
		}

		
		x_pos += 50;
		it++;
	}


	return true;
}

// Called each loop iteration
bool ctKenStageScene::PostUpdate()
{
	bool ret = true;

	if (quit_pressed)
		ret = false;

	return ret;
}

// Called before quitting
bool ctKenStageScene::CleanUp()
{
	LOG("Freeing KEN STAGE");

	return true;
}

bool ctKenStageScene::Load(pugi::xml_node& load)
{
	bool ret = true;

	return ret;
}

bool ctKenStageScene::Save(pugi::xml_node& save) const
{
	bool ret = true;

	return ret;
}

void ctKenStageScene::OnUITrigger(UIElement* elementTriggered, UI_State ui_state)
{
}

void ctKenStageScene::LoadAnimation(pugi::xml_node animation_node, ctAnimation* animation)
{
	bool ret = true;

	for (pugi::xml_node frame = animation_node.child("frame"); frame && ret; frame = frame.next_sibling("frame"))
		animation->PushBack({ frame.attribute("x").as_int() , frame.attribute("y").as_int(), frame.attribute("width").as_int(), frame.attribute("height").as_int() });

	animation->speed = animation_node.attribute("speed").as_float();
	animation->loop = animation_node.attribute("loop").as_bool();
}

void ctKenStageScene::LoadRect(pugi::xml_node rect_node, SDL_Rect* rect)
{
	rect->x = rect_node.attribute("x").as_float();
	rect->y = rect_node.attribute("y").as_float();
	rect->w = rect_node.attribute("width").as_float();
	rect->h = rect_node.attribute("height").as_float();
}

void ctKenStageScene::SetSceneAnimationsSpeed(float dt)
{
	girl.speed = girl_vel * dt;
	flag.speed = flag_vel * dt;
	two_guys.speed = two_guys_vel * dt;;
	green_guy.speed = green_guy_vel * dt;;
	blue_guy.speed = blue_guy_vel * dt;;
	fedora_guy.speed = fedora_guy_vel * dt;;
	pink_guy.speed = pink_guy_vel * dt;;
}

void ctKenStageScene::SetEntitiesSpeed(float dt)
{
	girl_vel = girl.speed;
	flag_vel = flag.speed;
	two_guys_vel = two_guys.speed;
	green_guy_vel = green_guy.speed;
	blue_guy_vel = blue_guy.speed;
	fedora_guy_vel = fedora_guy.speed;
	pink_guy_vel = pink_guy.speed;

	key_speed = true;
}