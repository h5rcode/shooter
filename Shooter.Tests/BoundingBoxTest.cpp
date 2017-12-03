
#include "gtest/gtest.h"
#include "BoundingBox.h"

TEST(BoundingBox_project, should_compute_the_expected_projection) {
	BoundingBox boundingBox(Vector2(), 1, 2, 0);

	Vector2 xAxis(1, 0);
	Vector2 yAxis(0, 1);

	Projection xAxisProjection = boundingBox.project(xAxis);
	Projection yAxisProjection = boundingBox.project(yAxis);

	EXPECT_EQ(-0.5, xAxisProjection.getMin());
	EXPECT_EQ(0.5, xAxisProjection.getMax());

	EXPECT_EQ(-1, yAxisProjection.getMin());
	EXPECT_EQ(1, yAxisProjection.getMax());
}

TEST(BoundingBox_intersects, should_return_true_when_bounding_boxes_intersect) {
	BoundingBox boundingBox1(Vector2(), 1, 2, 0);
	BoundingBox boundingBox2(Vector2(), 1, 2, 45);
	BoundingBox boundingBox3(Vector2(0.5, 1), 1, 2, 0);

	EXPECT_TRUE(boundingBox1.intersects(boundingBox2));
	EXPECT_TRUE(boundingBox1.intersects(boundingBox3));
}

TEST(BoundingBox_intersects, should_return_false_when_bounding_boxes_do_not_intersect) {
	BoundingBox boundingBox1(Vector2(), 1, 2, 0);
	BoundingBox boundingBox2(Vector2(2, 0), 1, 2, 0);
	BoundingBox boundingBox3(Vector2(0, 3), 1, 2, 0);

	EXPECT_FALSE(boundingBox1.intersects(boundingBox2));
	EXPECT_FALSE(boundingBox1.intersects(boundingBox3));
}