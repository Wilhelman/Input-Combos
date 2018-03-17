#include "ctDefs.h"
#include "ctLog.h"
#include "ctApp.h"
#include "ctInput.h"
#include "ctRender.h"
#include "ctInputCombo.h"
#include "ctPerfTimer.h"
#include "ctEntities.h"
#include "Player.h"

#include "InputEvent.h"
#include "Combo.h"

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


	for (pugi::xml_node combo_node = conf.child("combo"); combo_node && ret; combo_node = combo_node.next_sibling("combo"))
	{
		Combo* tmp_combo = new Combo();
		std::string tmp(combo_node.attribute("type").as_string());

		if (tmp == "SHORYUKEN")
			tmp_combo->SetType(ComboType::SHORYUKEN);
		//else if (tmp == "forward")
			//LoadAnimation(animations, &forward);

		for (pugi::xml_node input_node = combo_node.child("input_event"); input_node && ret; input_node = input_node.next_sibling("input_event"))
		{
			EventType tmp_type = EventType::NO_EVENT_TYPE;

			std::string tmp_event(input_node.attribute("type").as_string());

			if (tmp_event == "RIGHT")
				tmp_type = EventType::RIGHT;
			else if (tmp_event == "LEFT")
				tmp_type = EventType::LEFT;

			InputEvent* tmp_input_event = new InputEvent(input_node.attribute("time_limit").as_double(), tmp_type);

			tmp_combo->LoadInputEvent(tmp_input_event);
		}

		this->combo_list.push_back(tmp_combo);
	}

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

	//check for completed combo
	vector<Combo*>::const_iterator it = combo_list.begin();

	while (it != combo_list.end()) {

		if ((*it)->CheckForSolvedCombo(this->event_chain)) {
			App->entities->GetPlayer()->OnComboCompleted((*it)->GetType());
			this->CleanEventChain();
		}
			
		it++;

	}

	return ret;
}

// Called after all Updates
bool ctInputCombo::PostUpdate()
{
	bool ret = true;

	if (App->input->GetPadXAxis() < 0)
	{
		InputEvent* tmp_input_event = this->GetInputEventWithActionType(EventType::LEFT);
		event_chain.push_back(tmp_input_event);
	}
	else if (App->input->GetPadXAxis() > 0)
	{
		InputEvent* tmp_input_event = this->GetInputEventWithActionType(EventType::RIGHT);
		event_chain.push_back(tmp_input_event);
	}
	else if (App->input->GetPadYAxis() < 0)
	{
		InputEvent* tmp_input_event = this->GetInputEventWithActionType(EventType::UP);
		event_chain.push_back(tmp_input_event);
	}
	else if (App->input->GetPadYAxis() > 0)
	{
		InputEvent* tmp_input_event = this->GetInputEventWithActionType(EventType::DOWN);
		event_chain.push_back(tmp_input_event);
	}
	else if (App->input->GetPadXAxis() > 0 && App->input->GetPadYAxis() < 0)
	{
		InputEvent* tmp_input_event = this->GetInputEventWithActionType(EventType::UP_RIGHT);
		event_chain.push_back(tmp_input_event);
	}
	else if (App->input->GetPadXAxis() < 0 && App->input->GetPadYAxis() < 0)
	{
		InputEvent* tmp_input_event = this->GetInputEventWithActionType(EventType::UP_LEFT);
		event_chain.push_back(tmp_input_event);
	}
	else if (App->input->GetPadXAxis() > 0 && App->input->GetPadYAxis() > 0)
	{
		InputEvent* tmp_input_event = this->GetInputEventWithActionType(EventType::DOWN_RIGHT);
		event_chain.push_back(tmp_input_event);
	}
	else if (App->input->GetPadXAxis() < 0 && App->input->GetPadYAxis() > 0)
	{
		InputEvent* tmp_input_event = this->GetInputEventWithActionType(EventType::DOWN_LEFT);
		event_chain.push_back(tmp_input_event);
	}


	/*-------CHECK TIME IN ORDER TO DELETE INPUT EVENTS-------*/

	list<InputEvent*>::const_iterator it = event_chain.begin();

	while (it != event_chain.end()) {

		if ((*it)->GetTimer() > GENERIC_TIME_LIMIT) {
			delete *it;
			event_chain.erase(it);
		}

		it++;
	}

	LOG("Event Chain size: %i", event_chain.size());

	return ret;
}

// Called before quitting
bool ctInputCombo::CleanUp()
{
	bool ret = true;

	LOG("Freeing Input Combo!");

	//clean the input allocated in event chain
	this->CleanEventChain();

	//clean all the list of combos and their inputs in ~Combo()
	vector<Combo*>::const_iterator it_combo = combo_list.begin();

	while (it_combo != combo_list.end()) {
		delete *it_combo;
		it_combo++;
	}

	combo_list.clear();

	return ret;
}

InputEvent* ctInputCombo::GetInputEventWithActionType(EventType type) {

	if (event_chain.size() > 1) {
		InputEvent* last_input_event = event_chain.back();
		last_input_event->StopTimer();
	}

	ctPerfTimer tmp_timer;
	tmp_timer.Start();
	return new InputEvent(tmp_timer, type);

}

InputEvent* ctInputCombo::GetInputEventWithActionTypeAndTimeLimit(EventType type, double time_limit) {

	return new InputEvent(time_limit, type);
}

void ctInputCombo::CleanEventChain() {
	list<InputEvent*>::const_iterator it = event_chain.begin();

	while (it != event_chain.end()) {
		delete *it;
		it++;
	}

	event_chain.clear();
}

// class Input Combos ---------------------------------------------------

