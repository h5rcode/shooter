#include "Floor.h"

using namespace Shooter::World;

Floor::Floor(Vector2 position, int width, int length, double orientation, std::string texture) :
	_position(position),
	_width(width),
	_length(length),
	_orientation(orientation),
	_boundingBox(position, width, length, orientation),
	_texture(texture)
{
}

BoundingBox& Floor::getBoundingBox() {
	return _boundingBox;
}

Vector2& Floor::getPosition()
{
	return _position;
}

int Floor::getWidth() const
{
	return _width;
}

int Floor::getLength() const
{
	return _length;
}

double Floor::getOrientation() const
{
	return _orientation;
}

std::string& Floor::getTexture() {
	return _texture;
}