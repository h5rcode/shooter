#include "Wall.h"

Wall::Wall(Vector2 position, int width, int length, double orientation, std::string texture) :
	_position(position),
	_width(width),
	_length(length),
	_orientation(orientation),
	_texture(),
	_sprite(),
	_boundingBox(position, width, length, orientation)
{
	_texture.loadFromFile(texture);
	_texture.setRepeated(true);

	_sprite.setPosition(position.x, position.y);
	_sprite.setRotation(_orientation);
	_sprite.setTexture(_texture);
}

BoundingBox& Wall::getBoundingBox() {
	return _boundingBox;
}

Vector2& Wall::getPosition()
{
	return _position;
}

int Wall::getWidth() const
{
	return _width;
}

int Wall::getLength() const
{
	return _length;
}

double Wall::getOrientation() const
{
	return _orientation;
}

void Wall::render(sf::RenderWindow& renderWindow) {
	renderWindow.draw(_sprite);
}