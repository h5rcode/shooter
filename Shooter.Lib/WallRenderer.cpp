#include "WallRenderer.h"

using namespace Shooter::World;

WallRenderer::WallRenderer(sf::RenderWindow& renderWindow, IResourceManager& resourceManager) :
	_renderWindow(renderWindow),
	_resourceManager(resourceManager) {
}

void WallRenderer::render(Wall& wall)
{
	sf::Texture* texture = _resourceManager.getTexture(wall.getTexture());

	Vector2& position = wall.getPosition();
	int width = wall.getWidth();
	int length = wall.getLength();
	double orientation = wall.getOrientation();

	sf::Sprite sprite;
	sprite.setPosition((float)position.x, (float)position.y);
	sprite.setOrigin((float)width / 2, (float)length / 2);
	sprite.setRotation((float)orientation);
	sprite.setTexture(*texture);
	sprite.setTextureRect(sf::IntRect(0, 0, width, length));

	_renderWindow.draw(sprite);
}