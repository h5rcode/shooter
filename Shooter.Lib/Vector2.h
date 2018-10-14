#pragma once

namespace Shooter {
	namespace Math {
		class Vector2
		{
		public:
			double x;
			double y;

			Vector2(double x = 0, double y = 0);

			double getNorm() const;
			double computeAngleTo(Vector2& destination) const;
			double dotProduct(Vector2& vector) const;
			void multiply(double alpha);
			void normalize();
			void rotate(double angle);

			Vector2 &operator+=(const Vector2 &v);

			bool operator==(const Vector2 &v);
		};

		Vector2 multiply(const Vector2 &v, double alpha);

		Vector2 operator+(const Vector2 &v1, const Vector2 &v2);

		Vector2 operator-(const Vector2 &v1, const Vector2 &v2);
	}
}