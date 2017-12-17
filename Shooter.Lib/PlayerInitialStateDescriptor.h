#pragma once

#include "Vector2.h"

struct PlayerInitialStateDescriptor {
public:
	double x;
	double y;

	Vector2 getPosition();
};