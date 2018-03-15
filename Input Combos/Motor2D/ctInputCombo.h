#ifndef __ctInputCombo_H__
#define __ctInputCombo_H__

#include "ctModule.h"
#include "ctTimer.h"

#include <list>

using namespace std;

class InputEvent;

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

	//chain used to check the combos
	list<InputEvent*> event_chain;

	//non functional chain, used to
	list<InputEvent*> event_record;

};

#endif // __ctInputCombo_H__