#include "Prop.h"

Prop::Prop(std::string & texture)
	: _texture(texture)
{
}

bool Prop::collidesWith(Player& player) const {
	// TODO Implement collision detection.
	return false;
}

Vector2 & Prop::getPosition()
{
	return _position;
}

std::string & Prop::getTexture()
{
	return _texture;
}
