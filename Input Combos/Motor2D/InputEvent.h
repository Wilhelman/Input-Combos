#ifndef __InputEvent_H__
#define __InputEvent_H__

class ctPerfTimer;

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

	InputEvent(ctPerfTimer time_since_born, EventType type);
	virtual ~InputEvent();

	virtual void StopTimer();

public:

	ctPerfTimer timer;

private:

	EventType type = EventType::NO_TYPE;

	

};

#endif // __InputEvent_H__