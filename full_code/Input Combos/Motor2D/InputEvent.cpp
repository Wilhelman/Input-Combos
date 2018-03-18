#include "ctApp.h"
#include "InputEvent.h"
#include "ctRender.h"

#include "ctPerfTimer.h"

InputEvent::InputEvent(ctPerfTimer time_since_born, EventType type) : timer(time_since_born), type(type)
{
}

InputEvent::InputEvent(double time_limit, EventType type) : time_limit(time_limit), type(type)
{
}

InputEvent::~InputEvent()
{
}

EventType InputEvent::GetType()const {
	return this->type;
}

double InputEvent::GetTimer()const {
	return this->timer.ReadMs();
}

double InputEvent::GetTimeSinceBorn()const {
	if (time_since_born == 0.0)
		return this->timer.ReadMs();
	else
		return this->time_since_born;
}

double InputEvent::GetTimeLimit()const {
	return this->time_limit;
}

void InputEvent::StopTimer()
{
	this->time_since_born = this->timer.ReadMs();
}