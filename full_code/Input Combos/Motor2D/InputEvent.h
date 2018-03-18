#ifndef __InputEvent_H__
#define __InputEvent_H__

class ctPerfTimer;

enum EventType {
	RIGHT = 0,
	LEFT,
	UP,
	DOWN,
	PUNCH,
	KICK,

	NO_EVENT_TYPE
};


class InputEvent
{

public:

	// Constructor for incoming input event
	InputEvent(ctPerfTimer time_since_born, EventType type);

	// Constructor for the input events predefined by the combo
	InputEvent(double time_limit, EventType type);

	virtual ~InputEvent();

public:

	// Returns the event type of the Input Event
	EventType GetType()const;

	// Returns the time since the input event stopped the time
	double GetTimeSinceBorn()const;

	// Returns the time limit that has to pass since it is entered until the next one is pressed in milliseconds
	double GetTimeLimit()const;

	// Return the time of the input event since entered
	double GetTimer()const;

	// Stops the timer and sets the time_since_born
	void StopTimer();

private:

	// The type of the input event
	EventType type = EventType::NO_EVENT_TYPE;

	// Timer and variables used to give time between events and their limits
	ctPerfTimer timer;
	double time_limit = 0.0;
	double time_since_born = 0.0;

};

#endif // __InputEvent_H__