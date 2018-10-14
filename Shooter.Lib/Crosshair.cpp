#include "Crosshair.h"

using namespace Shooter::Math;
using namespace Shooter::World;

Crosshair::Crosshair(sf::Texture& texture) :
	_sprite()
{
	sf::Vector2u textureSize = texture.getSize();

	_sprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
	_sprite.setTexture(texture);
}

Vector2& Crosshair::getPosition()
{
	return _position;
}

void Crosshair::render(sf::RenderWindow& renderWindow) {
	_sprite.setPosition(_position.x, _position.y);
	renderWindow.draw(_sprite);
}
