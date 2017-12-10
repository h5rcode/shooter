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

	_sprite.setPosition((float)position.x, (float)position.y);
	_sprite.setOrigin((float)width / 2, (float)length / 2);
	_sprite.setRotation((float)_orientation);
	_sprite.setTexture(_texture);
	_sprite.setTextureRect(sf::IntRect(0, 0, width, length));
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