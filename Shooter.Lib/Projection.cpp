#include "Projection.h"

using namespace Shooter::Math;

Projection::Projection(double min, double max) :
	_min(min),
	_max(max)
{
}

double Projection::getMin() const {
	return _min;
}

double Projection::getMax() const {
	return _max;
}

bool Projection::overlaps(Projection& projection) const
{
	if (_min <= projection._min && projection._min <= _max)
	{
		return true;
	}

	if (_min <= projection._max && projection._max <= _max)
	{
		return true;
	}

	if (projection._min <= _min && _min <= projection._max) {
		return true;
	}

	return false;
}