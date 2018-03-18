#ifndef __Combo_H__
#define __Combo_H__

#include <vector>

using namespace std;

class InputEvent;

enum ComboType {
	SHORYUKEN = 0,
	TATSUMAKI,

	NO_DEF
};


class Combo
{

public:

	Combo();
	virtual ~Combo();

public:

	// GET|SET Combo type
	ComboType GetType()const;
	void SetType(ComboType type);

	// Load in the input_events vector of the combo the given input event
	void LoadInputEvent(InputEvent* input_event);

	// Compare the combo (this) with the volatile event_chain given by ctInputCombo | Return true if there is a total coincidence

	bool Combo::CheckForSolvedCombo(list<InputEvent*> event_chain)const;

private:

	// The type of the combo
	ComboType type = ComboType::NO_DEF;

	// A vector with all the input_events and their time limit that have one combo
	vector<InputEvent*> input_events;

};

#endif // __Combo_H__