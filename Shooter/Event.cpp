#include "Event.h"

Event::Event()
{
}

void Event::setType(EventType type) {
	_eventType = type;
}

EventType Event::getType() const
{
	return _eventType;
}
