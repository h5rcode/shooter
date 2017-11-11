#define _USE_MATH_DEFINES

#include "Wall.h"

Wall::Wall(Vector2 position, int width, int length, double orientation, std::string texture) :
	_position(position),
	_width(width),
	_length(length),
	_orientation(orientation),
	_texture(),
	_sprite()
{
	_texture.loadFromFile(texture);
	_texture.setRepeated(true);

	int angle = -180 * (_orientation - M_PI_2) / M_PI;

	_sprite.setPosition(position.x, position.y);
	_sprite.setRotation(angle);
	_sprite.setTexture(_texture);
}

Vector2 & Wall::getPosition()
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

bool Wall::collidesWith(Player& player) const
{
	// TODO Implement collision detection.
	return false;
}

void Wall::render(sf::RenderWindow& renderWindow) {
	renderWindow.draw(_sprite);
}