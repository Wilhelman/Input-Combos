#ifndef __ctInputCombo_H__
#define __ctInputCombo_H__

#include "ctModule.h"
#include <vector>

// ---------------------------------------------------
class ctInputCombo : public ctModule
{

	struct InputEvent {

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

	vector<InputEvent*> event_chain;

};

#endif // __ctInputCombo_H__