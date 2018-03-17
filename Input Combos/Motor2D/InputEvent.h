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

	NO_EVENT_TYPE
};

// ---------------------------------------------------
class InputEvent
{

public:

	InputEvent(ctPerfTimer time_since_born, EventType type);
	InputEvent(double time_limit, EventType type);
	virtual ~InputEvent();

public:

	//Returns the event type of the Input Event
	EventType GetType()const;

	//Returns the time since the Input Event was created in milliseconds
	double GetTimeSinceBorn()const;

	//Returns the time limit that has to pass since it is entered until the next one is pressed in milliseconds
	double GetTimeLimit()const;


	double GetTimer()const;

	//Stops the timer and sets the time_since_born
	void StopTimer();

private:

	EventType type = EventType::NO_EVENT_TYPE;
	ctPerfTimer timer;
	double time_limit = 0.0;
	double time_since_born = 0.0;
	

};

#endif // __InputEvent_H__