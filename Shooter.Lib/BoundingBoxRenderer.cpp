#include "BoundingBoxRenderer.h"

using namespace Shooter::Rendering::Renderers;

BoundingBoxRenderer::BoundingBoxRenderer(sf::RenderWindow& renderWindow) :
	_renderWindow(renderWindow),
	_vertexArray(sf::LineStrip, 5) {
}

void BoundingBoxRenderer::render(BoundingBox& boundingBox) {
	std::vector<std::shared_ptr<Vector2>>& vertices = boundingBox.getVertices();

	for (int i = 0; i < vertices.size(); i++)
	{
		std::shared_ptr<Vector2> vertex = vertices.at(i);
		_vertexArray[i].position = sf::Vector2f((float)vertex->x, (float)vertex->y);
	}

	_vertexArray[4].position = _vertexArray[0].position;

	_renderWindow.draw(_vertexArray);
}