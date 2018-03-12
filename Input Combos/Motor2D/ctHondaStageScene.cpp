#include "ctDefs.h"
#include "ctLog.h"
#include "ctApp.h"
#include "ctInput.h"
#include "ctTextures.h"
#include "ctAudio.h"
#include "ctRender.h"
#include "ctWindow.h"
#include "ctEntities.h"

#include "ctHondaStageScene.h"

#include "ctFadeToBlack.h"



ctHondaStageScene::ctHondaStageScene() : ctModule()
{
	name = "honda_stage";
}

// Destructor
ctHondaStageScene::~ctHondaStageScene()
{}

// Called before render is available

bool ctHondaStageScene::Awake(pugi::xml_node& conf)
{
	LOG("Loading HONDA STAGE");
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

	}

	//read rects from node
	for (pugi::xml_node rects = node->child("rects").child("rect"); rects && ret; rects = rects.next_sibling("rect"))
	{
		std::string tmp(rects.attribute("name").as_string());

		if (tmp == "ground")
			LoadRect(rects, ground);
		else if (tmp == "foreground")
			LoadRect(rects, foreground);
		else if (tmp == "background")
			LoadRect(rects, background);
	}

	return ret;
}

// Called before the first frame
bool ctHondaStageScene::Start()
{
	bool ret = true;

	LOG("HONDA STAGE start!");

	if (!App->audio->PlayMusic("audio/music/honda.ogg")) {
		ret = false;
		LOG("Error playing music in ctHondaStageScene Start");
	}

	return ret;
}

// Called each loop iteration
bool ctHondaStageScene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool ctHondaStageScene::Update(float dt)
{

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		this->quit_pressed = true;

	//if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->fadeToBlack->FadeIsOver())
	//App->fadeToBlack->FadeToBlackBetweenModules(this, this, 1.0f);

	return true;
}

// Called each loop iteration
bool ctHondaStageScene::PostUpdate()
{
	bool ret = true;

	if (quit_pressed)
		ret = false;

	return ret;
}

// Called before quitting
bool ctHondaStageScene::CleanUp()
{
	LOG("Freeing HONDA STAGE");

	return true;
}

bool ctHondaStageScene::Load(pugi::xml_node& load)
{
	bool ret = true;

	return ret;
}

bool ctHondaStageScene::Save(pugi::xml_node& save) const
{
	bool ret = true;

	return ret;
}

void ctHondaStageScene::OnUITrigger(UIElement* elementTriggered, UI_State ui_state)
{
}

void ctHondaStageScene::LoadAnimation(pugi::xml_node animation_node, ctAnimation* animation)
{
	bool ret = true;

	for (pugi::xml_node frame = animation_node.child("frame"); frame && ret; frame = frame.next_sibling("frame"))
		animation->PushBack({ frame.attribute("x").as_int() , frame.attribute("y").as_int(), frame.attribute("width").as_int(), frame.attribute("height").as_int() });

	animation->speed = animation_node.attribute("speed").as_float();
	animation->loop = animation_node.attribute("loop").as_bool();
}