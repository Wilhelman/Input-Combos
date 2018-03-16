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

	Combo *test_combo = new Combo();

	InputEvent* tmp_right = this->GetInputEventWithActionTypeAndTimeLimit(RIGHT, 1000);

	test_combo->input_events.push_back(tmp_right);

	InputEvent* tmp_left = this->GetInputEventWithActionTypeAndTimeLimit(LEFT, 1000);

	test_combo->input_events.push_back(tmp_left);

	combo_list.push_back(test_combo);

	return true;
}

// Called before all Updates
bool ctInputCombo::PreUpdate()
{
	bool ret = true;

	//check for combo
	vector<Combo*>::const_iterator it = combo_list.begin();

	while (it != combo_list.end()) {
		this->CheckForSolvedCombo((*it),this->event_chain);
		it++;
	}

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

	list<InputEvent*>::const_iterator it = event_chain.begin();

	while (it != event_chain.end()) {
		delete *it;
		it++;
	}

	event_chain.clear();

	return ret;
}

InputEvent* ctInputCombo::GetInputEventWithActionType(EventType type) {

	InputEvent* last_input_event = event_chain.back();

	if(last_input_event != nullptr)
		last_input_event->StopTimer();

	ctPerfTimer tmp_timer;
	tmp_timer.Start();
	return new InputEvent(tmp_timer, type);
}

InputEvent* ctInputCombo::GetInputEventWithActionTypeAndTimeLimit(EventType type, double time_limit) {

	return new InputEvent(time_limit, type);
}

bool ctInputCombo::CheckForSolvedCombo(Combo* combo_to_check, list<InputEvent*> event_chain) {
	
	list<InputEvent*>::const_iterator it_event_chain = event_chain.begin();
	vector<InputEvent*>::const_iterator it_combo_to_check = combo_to_check->input_events.begin();
	
	while (it_event_chain != event_chain.end()) {

		while (it_combo_to_check != combo_to_check->input_events.end()) {

			//Is this combo input equal to event_chain ?
			if (((*it_combo_to_check)->GetType() == (*it_event_chain)->GetType())) {

				//Is this combo input valid for a time limit ?
				if ((*it_combo_to_check)->GetTimeLimit() >= (*it_event_chain)->GetTimeSinceBorn()) {

					//Is the combo completed?
					if ((*it_combo_to_check) == combo_to_check->input_events.back()) {
						return true;
					}
					else { //Then continue checking the rest of inputs!

						if ((*it_event_chain) == event_chain.back())
							break;

						it_combo_to_check++;
						it_event_chain++;
						continue;
					}
				}
			}

			if ((*it_event_chain) == event_chain.back())
				break;

			it_event_chain++;
		}

		it_event_chain++;
	}
	
	//No combo solved?
	return false;
}

// class Input Combos ---------------------------------------------------

