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

// ---------------------------------------------------
class Combo
{

public:

	Combo();
	virtual ~Combo();

public:

	// GET|SET Combo type
	ComboType GetType()const;
	void SetType(ComboType type);

	void LoadInputEvent(InputEvent* input_event);

	bool Combo::CheckForSolvedCombo(list<InputEvent*> event_chain)const;

private:

	ComboType type = ComboType::NO_DEF;

	vector<InputEvent*> input_events;


};

#endif // __InputEvent_H__