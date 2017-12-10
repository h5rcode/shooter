#include "BoundingBox.h"

BoundingBox::BoundingBox(Vector2& position, int width, int height, double orientation) :
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
		std::shared_ptr<Vector2> nextVertex = _vertices.at((i + 1) % numberOfVertices);

		Vector2 edge = *nextVertex - *currentVertex;

		std::shared_ptr<Vector2> normal = std::make_shared<Vector2>(edge.y, -edge.x);
		normal->normalize();

		_normals.push_back(normal);
	}
}

std::vector<std::shared_ptr<Vector2>>& BoundingBox::getNormals() {
	return _normals;
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

void BoundingBox::render(sf::RenderWindow& renderWindow) {
	sf::VertexArray vertexArray(sf::Points, 0);
	for each (std::shared_ptr<Vector2> vertex in _vertices)
	{
		std::shared_ptr<sf::Vector2f> sfPosition = std::make_shared<sf::Vector2f>(vertex->x, vertex->y);
		std::shared_ptr<sf::Vertex> sfVertex = std::make_shared<sf::Vertex>(*sfPosition);
		vertexArray.append(*sfVertex);
	}

	renderWindow.draw(vertexArray);
}

bool BoundingBox::intersects(BoundingBox& boundingBox) const {
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