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

	// Get the volatile chain (only used for debug)
	list<InputEvent*> GetEventChain()const;

	// Get the combo list (only used for debug)
	int GetComboListSize()const;

private:
	
	// Generate one InputEvent of the given type (used for the incoming input)
	InputEvent* GetInputEventWithActionType(EventType type);

	// Generate one InputEvent of the given type and with limitation of time (used for defined combo)
	InputEvent* GetInputEventWithActionTypeAndTimeLimit(EventType type, double time_limit);

	// Cleans all the inputs events of the event_chain list
	void CleanEventChain();

private:

	// Chain used to check the combos
	list<InputEvent*> event_chain;

	// List of all combos posible, loaded by xml
	vector<Combo*> combo_list;

};

#endif // __ctInputCombo_H__