#ifndef __InputEvent_H__
#define __InputEvent_H__

#include "ctTimer.h"

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

// ---------------------------------------------------
class InputEvent
{

	

public:

	InputEvent(ctTimer time_since_born, EventType type);
	virtual ~InputEvent();

	virtual void StopTimer();

private:

	EventType type = EventType::NO_TYPE;

	ctTimer timer;

};

#endif // __InputEvent_H__