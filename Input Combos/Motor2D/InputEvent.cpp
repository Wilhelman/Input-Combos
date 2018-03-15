#include "ctApp.h"
#include "InputEvent.h"
#include "ctRender.h"

#include "ctPerfTimer.h"

InputEvent::InputEvent(ctPerfTimer time_since_born, EventType type) : timer(time_since_born), type(type)
{
}

InputEvent::~InputEvent()
{
}

void InputEvent::StopTimer()
{

}