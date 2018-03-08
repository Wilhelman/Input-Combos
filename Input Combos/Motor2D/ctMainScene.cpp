#include "ctDefs.h"
#include "ctLog.h"
#include "ctApp.h"
#include "ctInput.h"
#include "ctTextures.h"
#include "ctAudio.h"
#include "ctRender.h"
#include "ctWindow.h"
#include "ctEntities.h"

#include "ctMainScene.h"

#include "ctFadeToBlack.h"



ctMainScene::ctMainScene() : ctModule()
{
	name = "main_menu";
}

// Destructor
ctMainScene::~ctMainScene()
{}

// Called before render is available

bool ctMainScene::Awake()
{
	LOG("Loading Main Menu");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool ctMainScene::Start()
{
	bool ret = true;

	LOG("Main scene start!");

	/*if (!App->audio->PlayMusic("audio/music/8-bit_Detective.ogg")) {
		//ret = false;
		LOG("Error playing music in j1MainMenu Start");
	}*/

	return ret;
}

// Called each loop iteration
bool ctMainScene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool ctMainScene::Update(float dt)
{

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		this->quit_pressed = true;

	//if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->fadeToBlack->FadeIsOver())
		//App->fadeToBlack->FadeToBlackBetweenModules(this, this, 1.0f);

	return true;
}

// Called each loop iteration
bool ctMainScene::PostUpdate()
{
	bool ret = true;

	if (quit_pressed)
		ret = false;

	return ret;
}

// Called before quitting
bool ctMainScene::CleanUp()
{
	LOG("Freeing main_menu");
	
	return true;
}

bool ctMainScene::Load(pugi::xml_node& load)
{
	bool ret = true;

	return ret;
}

bool ctMainScene::Save(pugi::xml_node& save) const
{
	bool ret = true;

	return ret;
}

void ctMainScene::OnUITrigger(UIElement* elementTriggered, UI_State ui_state)
{
}