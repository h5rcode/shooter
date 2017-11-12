#include "BoundingBox.h"

BoundingBox::BoundingBox(Vector2& position, int width, int height, double orientation) :
	_normals(),
	_vertices()
{
	Vector2 topRight(width / 2, -height / 2);
	Vector2 bottomRight(width / 2, height / 2);
	Vector2 bottomLeft(-width / 2, height / 2);
	Vector2 topLeft(-width / 2, -height / 2);

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
		std::shared_ptr<Vector2> nextVertex = _vertices.at((i + 1) % numberOfVertices);

		Vector2 edge = *nextVertex - *currentVertex;

		std::shared_ptr<Vector2> normal = std::make_shared<Vector2>(-edge.y, edge.x);
		normal->normalize();

		_normals.push_back(normal);
	}
}

Projection BoundingBox::project(Vector2& axis) {
	std::shared_ptr<Vector2> vertex = _vertices.at(0);

	double min = axis.dotProduct(*vertex);
	double max = min;

	for (int i = 1; i < _normals.size(); i++)
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

bool BoundingBox::intersects(BoundingBox& boundingBox) {
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