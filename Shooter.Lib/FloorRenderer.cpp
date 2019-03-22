#include "FloorRenderer.h"

using namespace Shooter::World;

FloorRenderer::FloorRenderer(sf::RenderWindow& renderWindow, IResourceManager& resourceManager) :
	_renderWindow(renderWindow),
	_resourceManager(resourceManager) {
}

void FloorRenderer::render(Floor& floor)
{
	sf::Texture* texture = _resourceManager.getTexture(floor.getTexture());

	Vector2& position = floor.getPosition();
	int width = floor.getWidth();
	int length = floor.getLength();
	double orientation = floor.getOrientation();

	sf::Sprite sprite;
	sprite.setPosition((float)position.x, (float)position.y);
	sprite.setOrigin((float)width / 2, (float)length / 2);
	sprite.setRotation((float)orientation);
	sprite.setTexture(*texture);
	sprite.setTextureRect(sf::IntRect(0, 0, width, length));

	_renderWindow.draw(sprite);
}