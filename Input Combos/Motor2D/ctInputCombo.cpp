#include "ctDefs.h"
#include "ctLog.h"
#include "ctApp.h"
#include "ctInput.h"
#include "ctRender.h"

#include "ctInputCombo.h"
#include "InputEvent.h"
#include "ctPerfTimer.h"

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
		InputEvent* tmp_input_event = this->GetInputEventWithActionType(EventType::RIGHT);
		event_chain.push_back(tmp_input_event);
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN) {
		InputEvent* tmp_input_event = this->GetInputEventWithActionType(EventType::LEFT);
		event_chain.push_back(tmp_input_event);
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		InputEvent* tmp_input_event = this->GetInputEventWithActionType(EventType::HEAVY_KICK);
		event_chain.push_back(tmp_input_event);
	}

	list<InputEvent*>::const_iterator it = event_chain.begin();

	while (it != event_chain.end()) {

		if ((*it)->timer.ReadMs() > GENERIC_TIME_LIMIT)
			delete *it;

		it++;
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

InputEvent* ctInputCombo::GetInputEventWithActionType(EventType type) {
	ctPerfTimer tmp_timer;
	tmp_timer.Start();
	return new InputEvent(tmp_timer, type);
}

// class Input Combos ---------------------------------------------------

