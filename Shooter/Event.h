#pragma once

typedef enum EventType {
	MOUSE_BUTTON_DOWN,
	QUIT
} EventType;

class Event
{
public:
	Event();

	void setType(EventType type);
	EventType getType() const;

private:
	EventType _eventType;
};
