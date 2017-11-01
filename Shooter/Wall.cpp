#include "Wall.h"

Wall::Wall(Vector2 position, int width, int length, double orientation, std::string texture) :
	_position(position),
	_width(width),
	_length(length),
	_orientation(orientation),
	_texture(texture)
{
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

std::string & Wall::getTexture()
{
	return _texture;
}
