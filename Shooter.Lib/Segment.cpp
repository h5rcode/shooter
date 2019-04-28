#include "Segment.h"

using namespace Shooter::Math;

Segment::Segment(Vector2 origin, Vector2 end) :
	_origin(origin),
	_end(end) {}

Vector2& Segment::getOrigin() {
	return _origin;
}

Vector2& Segment::getEnd() {
	return _end;
}