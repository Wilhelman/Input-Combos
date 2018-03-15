#include "ctApp.h"
#include "InputEvent.h"
#include "ctRender.h"

InputEvent::InputEvent(ctTimer time_since_born, EventType type) : timer(time_since_born), type(type)
{
}

InputEvent::~InputEvent()
{
}

void InputEvent::StopTimer()
{

}