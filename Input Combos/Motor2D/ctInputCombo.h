#ifndef __ctInputCombo_H__
#define __ctInputCombo_H__

#define GENERIC_TIME_LIMIT 2000

#include "ctModule.h"

#include <list>
#include <vector>

using namespace std;

class InputEvent;
class Combo;
enum EventType;

// ---------------------------------------------------
class ctInputCombo : public ctModule
{

public:

	ctInputCombo();

	// Destructor
	virtual ~ctInputCombo();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

private:
	
	InputEvent* GetInputEventWithActionType(EventType type);

	InputEvent* GetInputEventWithActionTypeAndTimeLimit(EventType type, double time_limit);

private:

	//chain used to check the combos
	list<InputEvent*> event_chain;


	vector<Combo*> combo_list;

	//non functional chain, used to
	list<InputEvent*> event_record;

};

#endif // __ctInputCombo_H__