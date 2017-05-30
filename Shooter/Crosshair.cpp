#include "Crosshair.h"

Crosshair::Crosshair(std::string& texture) : _texture(texture)
{
}

Vector2& Crosshair::getPosition()
{
	return _position;
}

std::string& Crosshair::getTexture()
{
	return _texture;
}
