#pragma once

#include "Vector2.h"

using namespace Shooter::Math;

namespace Shooter {
	namespace World {
		struct Collision
		{
			Vector2 position;
			Vector2 normal;
		};
	}
}