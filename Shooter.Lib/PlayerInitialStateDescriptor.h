#pragma once

#include "Vector2.h"

using namespace Shooter::Math;

namespace Shooter {
	namespace LevelDescriptors {
		struct PlayerInitialStateDescriptor {
		public:
			double x;
			double y;

			Vector2 getPosition();
		};
	}
}