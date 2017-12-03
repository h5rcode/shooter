#include <cstdlib>

#include "gtest/gtest.h"
#include "Vector2.h"

TEST(Vector2Test_computeAngleTo, should_return_90_when_vectors_are_equal)
{
	double x = rand();
	double y = rand();

	Vector2 vector1(x, y);
	Vector2 vector2(x, y);

	double angle = vector1.computeAngleTo(vector2);

	EXPECT_EQ(90, angle);
}

TEST(Vector2Test_computeAngleTo, should_return_0_when_destination_vector_is_up)
{
	Vector2 center(0, 0);
	Vector2 up(0, -1);

	double angle = center.computeAngleTo(up);

	EXPECT_EQ(0, angle);
}

TEST(Vector2Test_computeAngleTo, should_return_0_when_destination_vector_is_right) {
	Vector2 center(0, 0);
	Vector2 right(1, 0);

	double angle = center.computeAngleTo(right);

	EXPECT_EQ(90, angle);
}

TEST(Vector2Test_computeAngleTo, should_return_minus_90_when_destination_vector_is_left) {
	Vector2 center(0, 0);
	Vector2 left(-1, 0);

	double angle = center.computeAngleTo(left);

	EXPECT_EQ(-90, angle);
}

TEST(Vector2Test_computeAngleTo, should_return_180_when_destination_vector_is_bottom) {
	Vector2 center(0, 0);
	Vector2 bottom(0, 1);

	double angle = center.computeAngleTo(bottom);

	EXPECT_EQ(180, angle);
}

TEST(Vector2Test_dotProduct, should_return_0_when_vectors_are_orthogonal) {
	Vector2 vector1(0, 1);
	Vector2 vector2(1, 0);

	double dotProduct = vector1.dotProduct(vector2);

	EXPECT_EQ(0, dotProduct);
}

TEST(Vector2Test_dotProduct, should_return_the_correct_value) {
	double x1 = rand();
	double y1 = rand();

	double x2 = rand();
	double y2 = rand();

	Vector2 vector1(x1, y1);
	Vector2 vector2(x2, y2);

	double dotProduct = vector1.dotProduct(vector2);

	double expectedDotProduct = x1 * x2 + y1 * y2;
	EXPECT_EQ(expectedDotProduct, dotProduct);
}

void rotate_should_update_the_vector_correctly(double x, double y, double angle, double expectedX, double expectedY) {
	double precision = 0.000001;

	Vector2 vector(x, y);
	vector.rotate(angle);

	EXPECT_NEAR(expectedX, vector.x, precision);
	EXPECT_NEAR(expectedY, vector.y, precision);
}

// TODO Make this test case a parameterized test case (https://github.com/google/googletest/blob/master/googletest/docs/AdvancedGuide.md#value-parameterized-tests)
TEST(Vector2Test_rotate, should_update_the_vector_correctly) {
	rotate_should_update_the_vector_correctly(1, 0, 90, 0, 1);
	rotate_should_update_the_vector_correctly(1, -1, -90, -1, -1);
	rotate_should_update_the_vector_correctly(1, 2, 180, -1, -2);
}

TEST(Vector2Test_getNorm, should_return_0_when_x_and_y_are_equal_to_0)
{
	Vector2 vector(0, 0);
	double norm = vector.getNorm();

	EXPECT_EQ(0, norm);
}

TEST(Vector2Test_getNorm, should_return_euclidian_norm_of_the_vector)
{
	double x = rand();
	double y = rand();

	double euclidianNorm = sqrt(x * x + y * y);

	Vector2 vector(x, y);
	double norm = vector.getNorm();

	EXPECT_EQ(euclidianNorm, norm);
}
