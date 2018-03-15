#ifndef __ctInputCombo_H__
#define __ctInputCombo_H__

#include "ctModule.h"
#include "ctTimer.h"

#include <list>

using namespace std;

// ---------------------------------------------------
class ctInputCombo : public ctModule
{

	enum EventType {
		RIGHT = 0,
		LEFT,
		UP,
		DOWN,
		LIGHT_PUNCH,
		HEAVY_PUNCH,
		LIGHT_KICK,
		HEAVY_KICK,

		NO_TYPE
	};

	struct InputEvent {
		EventType type;
		ctTimer timer;
	};

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

	bool Update();

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