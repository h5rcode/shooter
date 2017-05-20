#pragma once

#include "Event.h"

typedef enum Key {
	DOWN,
	LEFT,
	RIGHT,
	UP
} Key;

class IInputManager
{
public:
	virtual void getMouseState(int* mouseX, int* mouseY) = 0;
	virtual bool isKeyDown(Key key) = 0;
	virtual bool pollEvent(Event* event) = 0;
};
