#include "Prop.h"

Prop::Prop(Vector2 position, int width, int height, double orientation, std::string& texture) :
	_orientation(orientation),
	_sprite(),
	_texture(),
	_boundingBox(position, width, height, orientation)
{
	_texture.loadFromFile(texture);

	_sprite.setPosition((float)position.x, (float)position.y);
	_sprite.setOrigin((float)width / 2, (float)height / 2);
	_sprite.setRotation((float)_orientation);
	_sprite.setTexture(_texture);
	_sprite.setTextureRect(sf::IntRect(0, 0, width, height));
}

BoundingBox& Prop::getBoundingBox()
{
	return _boundingBox;
}

Vector2 & Prop::getPosition()
{
	return _position;
}

void Prop::render(sf::RenderWindow& renderWindow) {
	renderWindow.draw(_sprite);
}