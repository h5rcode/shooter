#include "gtest/gtest.h"
#include "CollisionHelper.h"

using namespace Shooter::World;

TEST(CollisionHelper_lineCollidesWithSegment, should_return_true_when_segment_is_aligned_with_line) {
	Vector2 a(0, 0);
	Vector2 b(1, 1);

	Vector2 o(2, 2);
	Vector2 p(3, 3);

	bool collide = lineCollidesWithSegment(a, b, o, p);

	EXPECT_TRUE(collide);
}

TEST(CollisionHelper_lineCollidesWithSegment, should_return_false_when_segment_is_parallel_to_line) {
	Vector2 a(0, 0);
	Vector2 b(1, 1);

	Vector2 o(0, 1);
	Vector2 p(1, 2);

	bool collide = lineCollidesWithSegment(a, b, o, p);

	EXPECT_FALSE(collide);
}

TEST(CollisionHelper_lineCollidesWithSegment, should_return_true_when_segment_crosses_line) {
	Vector2 a(5, 0);
	Vector2 b(5, 1);

	Vector2 o(0, 0);
	Vector2 p(4, 4);

	bool collide = lineCollidesWithSegment(a, b, o, p);

	EXPECT_FALSE(collide);
}

TEST(CollisionHelper_lineCollidesWithSegment, should_return_true_when_segment_touches_line) {
	Vector2 a(5, 0);
	Vector2 b(5, 5);

	Vector2 o(0, 1);
	Vector2 p(5, 1);

	bool collide = lineCollidesWithSegment(a, b, o, p);

	EXPECT_TRUE(collide);
}

TEST(CollisionHelper_lineCollidesWithSegment, should_return_false_when_segment_does_not_cross_line) {
	Vector2 a(5, 0);
	Vector2 b(5, 1);

	Vector2 o(0, 0);
	Vector2 p(4, 4);

	bool collide = lineCollidesWithSegment(a, b, o, p);

	EXPECT_FALSE(collide);
}

TEST(CollisionHelper_segmentsCollide, should_return_true_when_segments_touch) {
	Vector2 a1(0, 0);
	Vector2 b1(1, 0);

	Vector2 a2(1, 0);
	Vector2 b2(1, 1);

	bool collide = segmentsCollide(a1, b1, a2, b2);

	EXPECT_TRUE(collide);
}

TEST(CollisionHelper_computeRelativeIntersectionPoint, should_return_0_5_when_ab_intersects_op_at_half_its_length) {
	Vector2 a(0, 0);
	Vector2 b(2, 0);

	Vector2 o(1, 0);
	Vector2 p(1, 1);

	double k = computeRelativeIntersectionPoint(a, b, o, p);
	EXPECT_EQ(0.5, k);
}

TEST(CollisionHelper_computeRelativeIntersectionPoint, should_return_0_when_ab_intersects_op_at_its_origin) {
	Vector2 a(0, 0);
	Vector2 b(2, 0);

	Vector2 o(0, 1);
	Vector2 p(2, 1);

	double k = computeRelativeIntersectionPoint(a, b, o, p);
	EXPECT_EQ(0, k);
}
