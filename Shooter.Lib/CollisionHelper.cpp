#include <stdexcept>

#include "CollisionHelper.h"

using namespace Shooter::World;

double Shooter::World::computeRelativeIntersectionPoint(Vector2& a, Vector2& b, Vector2& o, Vector2& p) {
	Vector2 ab = b - a;
	Vector2 op = p - o;

	double determinantAbOp = determinant(ab, op);

	if (determinantAbOp == 0) {
		Vector2 ao = o - a;

		if (ab.x != 0) {
			return ao.x / ab.x;
		}

		if (ab.y != 0) {
			return ao.y / ab.y;
		}

		return 0;
	}

	return -(a.x * op.y - o.x * op.y - op.x * a.y + op.x * o.y) / determinantAbOp;
}

bool Shooter::World::lineCollidesWithSegment(Vector2& a, Vector2& b, Vector2& o, Vector2& p) {
	Vector2 ab = b - a;
	Vector2 ao = o - a;
	Vector2 ap = p - a;

	double determinantO = determinant(ab, ao);
	double determinantP = determinant(ab, ap);

	return determinantO * determinantP <= 0;
}

bool Shooter::World::segmentsCollide(Vector2& a1, Vector2& b1, Vector2& a2, Vector2& b2) {
	return lineCollidesWithSegment(a1, b1, a2, b2) && lineCollidesWithSegment(a2, b2, a1, b1);
}
