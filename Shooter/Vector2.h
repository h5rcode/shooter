#pragma once

class Vector2
{
public:
	double x;
	double y;

	Vector2(double x = 0, double y = 0);

	double getNorm() const;

	double computeAngleTo(Vector2& destination) const;
	void multiply(double alpha);
	void normalize();

	Vector2 &operator+=(const Vector2 &v);
};

Vector2 multiply(const Vector2 &v, double alpha);

Vector2 operator+(const Vector2 &v1, const Vector2 &v2);
