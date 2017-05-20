#pragma once

#include "Vector2.h"

class Crosshair
{
public:
	Crosshair();

	Vector2* getPosition();

private:
	Vector2 _position;
};

