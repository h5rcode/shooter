#pragma once

#include <memory>
#include <vector>

#include "Collision.h"
#include "Projection.h"
#include "Vector2.h"

using namespace Shooter::Math;

namespace Shooter {
	namespace World {
		class BoundingBox {
		public:
			BoundingBox(Vector2& position, int width, int height, double orientation);

		public:
			int getHeight() const;
			std::vector<std::shared_ptr<Vector2>>& getNormals();
			int getWidth() const;
			bool intersects(BoundingBox& boundingBox) const;
			Projection project(Vector2& axis) const;
			std::vector<std::shared_ptr<Collision>> computeCollisionsWithSegment(Vector2& segmentOrigin, Vector2& segmentEnd);

		private:
			double _height;
			double _width;

			double _minX;
			double _maxX;
			double _minY;
			double _maxY;

			std::vector<std::shared_ptr<Vector2>> _vertices;
			std::vector<std::shared_ptr<Vector2>> _normals;
		};
	}
}