#include "BoundingBox.h"
#include "CollisionHelper.h"

using namespace Shooter::Math;
using namespace Shooter::World;

BoundingBox::BoundingBox(Vector2& position, int width, int height, double orientation) :
	_height(height),
	_width(width),
	_normals(),
	_vertices()
{
	double halfWidth = width / 2.f;
	double halfHeight = height / 2.f;

	Vector2 topRight(halfWidth, -halfHeight);
	Vector2 bottomRight(halfWidth, halfHeight);
	Vector2 bottomLeft(-halfWidth, halfHeight);
	Vector2 topLeft(-halfWidth, -halfHeight);

	topRight.rotate(orientation);
	bottomRight.rotate(orientation);
	bottomLeft.rotate(orientation);
	topLeft.rotate(orientation);

	std::shared_ptr<Vector2> vertex1 = std::make_shared<Vector2>(position + topRight);
	std::shared_ptr<Vector2> vertex2 = std::make_shared<Vector2>(position + bottomRight);
	std::shared_ptr<Vector2> vertex3 = std::make_shared<Vector2>(position + bottomLeft);
	std::shared_ptr<Vector2> vertex4 = std::make_shared<Vector2>(position + topLeft);

	_vertices.push_back(vertex1);
	_vertices.push_back(vertex2);
	_vertices.push_back(vertex3);
	_vertices.push_back(vertex4);

	int numberOfVertices = _vertices.size();
	for (int i = 0; i < numberOfVertices; i++)
	{
		std::shared_ptr<Vector2> currentVertex = _vertices.at(i);

		if (i == 0) {
			_minX = currentVertex->x;
			_maxX = currentVertex->x;
			_minY = currentVertex->y;
			_maxY = currentVertex->y;
		}
		else {
			if (currentVertex->x < _minX) {
				_minX = currentVertex->x;
			}

			if (currentVertex->x > _maxX) {
				_maxX = currentVertex->x;
			}

			if (currentVertex->y < _minY) {
				_minY = currentVertex->y;
			}

			if (currentVertex->y > _maxY) {
				_maxY = currentVertex->y;
			}
		}

		std::shared_ptr<Vector2> nextVertex = _vertices.at((i + 1) % numberOfVertices);

		Vector2 edge = *nextVertex - *currentVertex;

		std::shared_ptr<Vector2> normal = std::make_shared<Vector2>(edge.y, -edge.x);
		normal->normalize();

		_normals.push_back(normal);
	}
}

std::vector<std::shared_ptr<Collision>> BoundingBox::computeCollisionsWithSegment(Vector2& segmentOrigin, Vector2& segmentEnd) {
	int numberOfVertices = _vertices.size();

	double segmentOriginX = segmentOrigin.x;
	double segmentOriginY = segmentOrigin.y;

	double segmentEndX = segmentEnd.x;
	double segmentEndY = segmentEnd.y;

	Vector2 segment = segmentEnd - segmentOrigin;

	int collisionCount = 0;

	std::vector<std::shared_ptr<Collision>> collisions;
	for (int i = 0; i < numberOfVertices; i++) {
		std::shared_ptr<Vector2> edgeOrigin = _vertices.at(i);
		std::shared_ptr<Vector2> edgeEnd = _vertices.at((i + 1) % numberOfVertices);

		if (!Shooter::World::segmentsCollide(segmentOrigin, segmentEnd, *edgeOrigin, *edgeEnd)) {
			continue;
		}

		double k = computeRelativeIntersectionPoint(segmentOrigin, segmentEnd, *edgeOrigin, *edgeEnd);

		if (k >= 0 && k <= 1) {
			Vector2 impactRelativeToSegmentOrigin = segment;
			impactRelativeToSegmentOrigin.multiply(k);
			std::shared_ptr<Vector2> collisionNormal = _normals.at(i);

			std::shared_ptr<Collision> collision = std::make_shared<Collision>();

			collision->normal = *collisionNormal;
			collision->position = segmentOrigin + impactRelativeToSegmentOrigin;

			collisions.push_back(collision);

			collisionCount++;

			if (collisionCount > 1) {
				int a = 3;
			}
		}
	}

	return collisions;
}

int BoundingBox::getHeight() const {
	return _height;
}

std::vector<std::shared_ptr<Vector2>>& BoundingBox::getNormals() {
	return _normals;
}

int BoundingBox::getWidth() const {
	return _width;
}

Projection BoundingBox::project(Vector2& axis) const {
	std::shared_ptr<Vector2> vertex = _vertices.at(0);

	double min = axis.dotProduct(*vertex);
	double max = min;

	for (size_t i = 1; i < _normals.size(); i++)
	{
		vertex = _vertices.at(i);
		double dotProduct = axis.dotProduct(*vertex);

		if (dotProduct < min) {
			min = dotProduct;
		}
		else if (dotProduct > max) {
			max = dotProduct;
		}
	}

	return Projection(min, max);
}

bool BoundingBox::intersects(BoundingBox& boundingBox) const {
	if ((_maxX < boundingBox._minX || boundingBox._maxX < _minX) && (_maxY < boundingBox._minY || boundingBox._maxY < _minY)) {
		return false;
	}

	for each (std::shared_ptr<Vector2> normal in _normals)
	{
		Projection boundingBoxProjection = boundingBox.project(*normal);
		Projection thisProjection = project(*normal);

		if (thisProjection.overlaps(boundingBoxProjection) == false) {
			return false;
		}
	}

	for each (std::shared_ptr<Vector2> normal in boundingBox._normals)
	{
		Projection boundingBoxProjection = boundingBox.project(*normal);
		Projection thisProjection = project(*normal);

		if (thisProjection.overlaps(boundingBoxProjection) == false) {
			return false;
		}
	}

	return true;
}