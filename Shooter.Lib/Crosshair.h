#pragma once

#include "Vector2.h"

using namespace Shooter::Math;

namespace Shooter {
	namespace World {
		class Crosshair
		{
		public:
			Vector2& getPosition();

		private:
			Vector2 _position;
		};
	}
}

