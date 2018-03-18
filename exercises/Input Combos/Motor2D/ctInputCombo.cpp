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

//#include "Brofiler\Brofiler.h"

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
		else if (tmp == "TATSUMAKI")
			tmp_combo->SetType(ComboType::TATSUMAKI);

		for (pugi::xml_node input_node = combo_node.child("input_event"); input_node && ret; input_node = input_node.next_sibling("input_event"))
		{
			EventType tmp_type = EventType::NO_EVENT_TYPE;

			std::string tmp_event(input_node.attribute("type").as_string());

			if (tmp_event == "RIGHT")
				tmp_type = EventType::RIGHT;
			else if (tmp_event == "LEFT")
				tmp_type = EventType::LEFT;
			else if (tmp_event == "DOWN")
				tmp_type = EventType::DOWN;
			else if (tmp_event == "PUNCH")
				tmp_type = EventType::PUNCH;
			else if (tmp_event == "KICK")
				tmp_type = EventType::KICK;

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
	//BROFILER_CATEGORY("Combo comparison", Profiler::Color::Green);

	bool ret = true;

	//check for completed combo
	vector<Combo*>::const_iterator it = combo_list.begin();

	while (it != combo_list.end()) {

		if ((*it)->CheckForSolvedCombo(this->event_chain)) {
			App->entities->GetPlayer()->OnComboCompleted((*it)->GetType());
			this->CleanEventChain();
			break;
		}
			
		it++;

	}

	return ret;
}

// Called after all Updates
bool ctInputCombo::PostUpdate()
{
	//BROFILER_CATEGORY("Input event entry + delete ", Profiler::Color::Blue);

	bool ret = true;

	//TODO 1: Create the InputEvents from its constructor. Use the "GetInputEventWithActionType" function for each type of input.

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || App->input->gamepad.CROSS_RIGHT == GAMEPAD_STATE::PAD_BUTTON_DOWN) {
		event_chain.push_back(this->GetInputEventWithActionType(EventType::RIGHT));
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || App->input->gamepad.CROSS_LEFT == GAMEPAD_STATE::PAD_BUTTON_DOWN) {
		event_chain.push_back(this->GetInputEventWithActionType(EventType::LEFT));
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || App->input->gamepad.CROSS_DOWN == GAMEPAD_STATE::PAD_BUTTON_DOWN) {
		event_chain.push_back(this->GetInputEventWithActionType(EventType::DOWN));
	}

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || App->input->gamepad.CROSS_UP == GAMEPAD_STATE::PAD_BUTTON_DOWN) {
		event_chain.push_back(this->GetInputEventWithActionType(EventType::UP));
	}

	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN || App->input->gamepad.X == GAMEPAD_STATE::PAD_BUTTON_DOWN || App->input->gamepad.Y == GAMEPAD_STATE::PAD_BUTTON_DOWN) {
		event_chain.push_back(this->GetInputEventWithActionType(EventType::PUNCH));
	}

	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN || App->input->gamepad.B == GAMEPAD_STATE::PAD_BUTTON_DOWN || App->input->gamepad.A == GAMEPAD_STATE::PAD_BUTTON_DOWN) {
		event_chain.push_back(this->GetInputEventWithActionType(EventType::KICK));
	}

	/*-------CHECK TIME IN ORDER TO DELETE INPUT EVENTS-------*/

	//TODO DELETE INPUT BUFER

	//LOG("Event Chain size: %i", event_chain.size());

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

	//TODO 5? STOP TIMERS

	//TODO 1: Start the timer for the new InputEvent and call the constructor of the InputEvent class.
	///Hint: You've to choose between two constructors, check InputEvent.h!


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

list<InputEvent*> ctInputCombo::GetEventChain()const {
	return this->event_chain;
}

// class Input Combos ---------------------------------------------------

