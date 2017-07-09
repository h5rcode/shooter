#include "Wall.h"

Wall::Wall(Vector2 start, Vector2 end, std::string texture) :
	_start(start),
	_end(end),
	_texture(texture)
{
}

bool Wall::collidesWith(Player& player) const
{
	// TODO Implement collision detection.
	return false;
}

Vector2 & Wall::getStart()
{
	return _start;
}

Vector2 & Wall::getEnd()
{
	return _end;
}

std::string & Wall::getTexture()
{
	return _texture;
}
