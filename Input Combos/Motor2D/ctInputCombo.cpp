#include "ctDefs.h"
#include "ctLog.h"
#include "ctApp.h"
#include "ctInput.h"
#include "ctRender.h"

#include "ctInputCombo.h"
#include "InputEvent.h"

ctInputCombo::ctInputCombo() : ctModule()
{
	name = "input_combo";
}

// Destructor
ctInputCombo::~ctInputCombo()
{}

// Called before render is available
bool ctInputCombo::Awake(pugi::xml_node& conf)
{
	bool ret = true;

	LOG("Get up Input Combo!");

	return ret;
}

// Called before the first frame
bool ctInputCombo::Start()
{
	bool ret = true;

	LOG("Start Input Combo!");

	return true;
}

// Called before all Updates
bool ctInputCombo::PreUpdate()
{
	bool ret = true;


	return ret;
}

// Called after all Updates
bool ctInputCombo::PostUpdate()
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN) {
		ctTimer tmp_timer;
		tmp_timer.SetStartTime(SDL_GetTicks());
		InputEvent* tmp = new InputEvent(tmp_timer, EventType::RIGHT);
		event_chain.push_back(tmp);
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN) {

	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {

	}

	return ret;
}

// Called before quitting
bool ctInputCombo::CleanUp()
{
	bool ret = true;

	LOG("Freeing Input Combo!");

	list<InputEvent*>::const_iterator it = event_chain.begin();

	while (it != event_chain.end()) {
		delete *it;
		it++;
	}
	event_chain.clear();

	return ret;
}

// class Input Combos ---------------------------------------------------

