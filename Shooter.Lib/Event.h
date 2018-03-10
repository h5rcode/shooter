#pragma once

typedef enum EventType {
	NOTHING = 0,
	LEFT_BUTTON_CLICKED = 1,
	RIGHT_BUTTON_CLICKED = 2,
	QUIT = 3
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
