#pragma once

#include "Vector2.h"

namespace Shooter {
	namespace Math {
		class Segment {
		public:
			Segment(Vector2 origin, Vector2 end);
		public:
			Vector2& getOrigin();
			Vector2& getEnd();
		private:
			Vector2 _origin;
			Vector2 _end;
		};
	}
}