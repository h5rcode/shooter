#pragma once

#include "Vector2.h"

using namespace Shooter::Math;

namespace Shooter {
	namespace World {
		double computeRelativeIntersectionPoint(Vector2& a1, Vector2& b1, Vector2& a2, Vector2& b2);
		bool lineCollidesWithSegment(Vector2& a, Vector2& b, Vector2& o, Vector2& p);
		bool segmentsCollide(Vector2& a1, Vector2& b1, Vector2& a2, Vector2& b2);
	}
}