#include <cstdlib>

#include "gtest/gtest.h"
#include "Vector2.h"

TEST(Vector2Test, getNorm_should_return_0_when_x_and_y_are_equal_to_0)
{
	Vector2 vector(0, 0);
	double norm = vector.getNorm();

	EXPECT_EQ(0, norm);
}

TEST(Vector2Test, getNorm_should_return_euclidian_norm_of_the_vector)
{
	double x = rand();
	double y = rand();

	double euclidianNorm = sqrt(x * x + y * y);

	Vector2 vector(x, y);
	double norm = vector.getNorm();

	EXPECT_EQ(euclidianNorm, norm);
}

TEST(Vector2Test, computeAngleTo_should_return_90_when_vectors_are_equal)
{
	double x = rand();
	double y = rand();

	Vector2 vector1(x, y);
	Vector2 vector2(x, y);

	double angle = vector1.computeAngleTo(vector2);

	EXPECT_EQ(90, angle);
}

TEST(Vector2Test, computeAngleTo_should_return_0_when_destination_vector_is_up)
{
	Vector2 center(0, 0);
	Vector2 up(0, -1);

	double angle = center.computeAngleTo(up);

	EXPECT_EQ(0, angle);
}

TEST(Vector2Test, computeAngleTo_should_return_0_when_destination_vector_is_right) {
	Vector2 center(0, 0);
	Vector2 right(1, 0);

	double angle = center.computeAngleTo(right);

	EXPECT_EQ(90, angle);
}

TEST(Vector2Test, computeAngleTo_should_return_minus_90_when_destination_vector_is_left) {
	Vector2 center(0, 0);
	Vector2 left(-1, 0);

	double angle = center.computeAngleTo(left);

	EXPECT_EQ(-90, angle);
}

TEST(Vector2Test, computeAngleTo_should_return_180_when_destination_vector_is_bottom) {
	Vector2 center(0, 0);
	Vector2 bottom(0, 1);

	double angle = center.computeAngleTo(bottom);

	EXPECT_EQ(180, angle);
}
