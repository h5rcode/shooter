#include "Prop.h"

Prop::Prop(Vector2 position, int width, int height, double orientation, std::string& texture) :
	_texture(texture),
	_boundingBox(position, width, height, orientation)
{
}

BoundingBox& Prop::getBoundingBox()
{
	return _boundingBox;
}

Vector2 & Prop::getPosition()
{
	return _position;
}

std::string & Prop::getTexture()
{
	return _texture;
}
