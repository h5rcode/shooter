#include "Wall.h"

using namespace Shooter::World;

Wall::Wall(Vector2 position, int width, int length, double orientation, std::string texture) :
	_position(position),
	_width(width),
	_length(length),
	_orientation(orientation),
	_boundingBox(position, width, length, orientation),
	_texture(texture)
{
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

std::string& Wall::getTexture() {
	return _texture;
}