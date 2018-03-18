#include "ctApp.h"
#include "InputEvent.h"
#include "ctRender.h"
#include "Combo.h"

Combo::Combo()
{
}

Combo::~Combo()
{

	vector<InputEvent*>::const_iterator it_combo_to_check = this->input_events.begin();

	while (it_combo_to_check != this->input_events.end()) {
		delete *it_combo_to_check;
		it_combo_to_check++;
	}

	input_events.clear();

}

void Combo::LoadInputEvent(InputEvent* input_event) {
	this->input_events.push_back(input_event);
}

void Combo::SetType(ComboType type){
	this->type = type;
}

ComboType Combo::GetType()const {
	return this->type;
}

bool Combo::CheckForSolvedCombo(list<InputEvent*> event_chain) const{

	list<InputEvent*>::const_iterator it_event_chain = event_chain.begin();
	vector<InputEvent*>::const_iterator it_combo_to_check = this->input_events.begin();

	while (it_event_chain != event_chain.end()) {

		it_combo_to_check = this->input_events.begin();
		
		while (it_combo_to_check != this->input_events.end()) {

			//Is this combo input equal to event_chain ?
			if (((*it_combo_to_check)->GetType() == (*it_event_chain)->GetType())) {

				//Is this combo input valid for a time limit ?
				if ((*it_combo_to_check)->GetTimeLimit() >= (*it_event_chain)->GetTimeSinceBorn()) {

					//Is the combo completed?
					if ((*it_combo_to_check) == this->input_events.back()) {
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
				else {
					break;
				}
			}
			else {
				break;
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