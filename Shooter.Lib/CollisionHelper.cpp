#include <stdexcept>

#include "CollisionHelper.h"

using namespace Shooter::World;

std::shared_ptr<Collision> Shooter::World::computeCollisionBetweenSegments(Vector2& a, Vector2& b, Vector2& o, Vector2& p) {

	if (!segmentsCollide(a, b, o, p)) {
		return nullptr;
	}

	double k = computeRelativeIntersectionPoint(a, b, o, p);
	if (k < 0 || k > 1) {
		return nullptr;
	}

	Vector2 ab = b - a;
	Vector2 op = p - o;

	Vector2 impactRelativeToA = ab;
	impactRelativeToA.multiply(k);

	Vector2 position = a + impactRelativeToA;
	Vector2 normal = Vector2(op.y, -op.x);
	normal.normalize();

	double dotProductAbNormal = ab.dotProduct(normal);
	if (dotProductAbNormal > 0) {
		normal = multiply(normal, -1);
	}

	std::shared_ptr<Collision> collision = std::make_shared<Collision>();
	collision->normal = normal;
	collision->position = position;

	return collision;
}

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
