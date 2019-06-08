
#include "gtest/gtest.h"
#include "BoundingBox.h"

using namespace Shooter::Math;
using namespace Shooter::World;

void expectVectorsAreNearEqual(Vector2& expectedVector, Vector2& actualVector) {
	double precision = 0.000001;

	EXPECT_NEAR(expectedVector.x, actualVector.x, precision);
	EXPECT_NEAR(expectedVector.y, actualVector.y, precision);
}

TEST(BoudingBox_testCollisionWithSegment, should_return_2_collisions_when_the_segment_collides_at_the_corner_of_the_box) {
	BoundingBox boundingBox(Vector2(2, 2), 4, 4, 0);

	std::vector<std::shared_ptr<Collision>> collisions = boundingBox.computeCollisionsWithSegment(Vector2(-1, 0), Vector2(0, 0));

	EXPECT_EQ(2, collisions.size());

	std::shared_ptr<Collision> collision1 = collisions.at(0);
	std::shared_ptr<Collision> collision2 = collisions.at(1);

	EXPECT_EQ(0, collision1->position.x);
	EXPECT_EQ(0, collision1->position.y);
	EXPECT_EQ(-1, collision1->normal.x);
	EXPECT_EQ(0, collision1->normal.y);

	EXPECT_EQ(0, collision2->position.x);
	EXPECT_EQ(0, collision2->position.y);
	EXPECT_EQ(0, collision2->normal.x);
	EXPECT_EQ(-1, collision2->normal.y);
}

TEST(BoudingBox_testCollisionWithSegment, should_return_false_when_the_box_does_not_collide_with_the_segment) {
	BoundingBox boundingBox(Vector2(2, 2), 4, 4, 0);

	std::vector<std::shared_ptr<Collision>> collisions = boundingBox.computeCollisionsWithSegment(Vector2(-1, 2), Vector2(-2, 2));

	// TODO EXPECT_FALSE(testResult.collides);
}

TEST(BoundingBox_getNormals, should_return_the_expected_normals) {
	double precision = 0.000001;

	BoundingBox boundingBox(Vector2(), 2, 2, 45);

	std::vector<std::shared_ptr<Vector2>>& normals = boundingBox.getNormals();

	std::shared_ptr<Vector2> normal1 = normals.at(0);
	std::shared_ptr<Vector2> normal2 = normals.at(1);
	std::shared_ptr<Vector2> normal3 = normals.at(2);
	std::shared_ptr<Vector2> normal4 = normals.at(3);

	double halfSqrt2 = sqrt(2.f) / 2.f;

	expectVectorsAreNearEqual(Vector2(halfSqrt2, halfSqrt2), *normal1);
	expectVectorsAreNearEqual(Vector2(-halfSqrt2, halfSqrt2), *normal2);
	expectVectorsAreNearEqual(Vector2(-halfSqrt2, -halfSqrt2), *normal3);
	expectVectorsAreNearEqual(Vector2(halfSqrt2, -halfSqrt2), *normal4);
}

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