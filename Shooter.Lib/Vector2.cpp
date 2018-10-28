#define _USE_MATH_DEFINES

#include "Vector2.h"
#include <math.h>

using namespace Shooter::Math;

Vector2::Vector2(double x, double y)
{
	this->x = x;
	this->y = y;
}

double Vector2::getNorm() const
{
	return sqrt(this->x * this->x + this->y * this->y);
}

double Vector2::computeAngleTo(Vector2& destination) const
{
	double xDest = destination.x;
	double yDest = destination.y;

	double x = this->x;
	double y = this->y;

	double alpha;

	if (x == xDest && y == yDest) {
		alpha = 0;
	}
	else {
		double cosAlpha = (xDest - this->x) / sqrt((yDest - y) * (yDest - y) + (xDest - x)  * (xDest - x));
		alpha = acos(cosAlpha);

		if (yDest > this->y)
		{
			alpha = -alpha;
		}
	}

	return 90.f - 180.f * alpha / M_PI;
}

double Vector2::dotProduct(Vector2& vector) const
{
	return this->x * vector.x + this->y * vector.y;
}

void Vector2::multiply(double alpha)
{
	this->x *= alpha;
	this->y *= alpha;
}

void Vector2::normalize()
{
	double norm = getNorm();
	if (norm == 0)
	{
		this->x = 0;
		this->y = 0;
	}
	else
	{
		this->x /= norm;
		this->y /= norm;
	}
}

void Vector2::rotate(double angleInDegrees) {
	double angleInRadians = M_PI * angleInDegrees / 180.f;

	double cosineAngle = cos(angleInRadians);
	double sineAngle = sin(angleInRadians);

	double x = this->x;
	double y = this->y;

	this->x = x * cosineAngle - y * sineAngle;
	this->y = x * sineAngle + y * cosineAngle;
}

Vector2 &Vector2::operator+=(const Vector2 &v)
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}

bool Vector2::operator==(const Vector2 &v)
{
	return (this->x == v.x) && (this->y == v.y);
}

bool Vector2::operator!=(const Vector2 &v)
{
	return (this->x != v.x) || (this->y != v.y);
}

Vector2 Shooter::Math::multiply(const Vector2 &v, double alpha)
{
	return Vector2(alpha * v.x, alpha * v.y);
}

Vector2 Shooter::Math::operator+(const Vector2 &v1, const Vector2 &v2)
{
	return Vector2(v1.x + v2.x, v1.y + v2.y);
}

Vector2 Shooter::Math::operator-(const Vector2 &v1, const Vector2 &v2)
{
	return Vector2(v1.x - v2.x, v1.y - v2.y);
}
