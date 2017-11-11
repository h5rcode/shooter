#include "Crosshair.h"

Crosshair::Crosshair(std::string& texture) :
	_texture(),
	_sprite()
{
	_texture.loadFromFile(texture.c_str());

	sf::Vector2u textureSite = _texture.getSize();
	_sprite.setOrigin(textureSite.x / 2, textureSite.y / 2);
	_sprite.setTexture(_texture);
}

Vector2& Crosshair::getPosition()
{
	return _position;
}

void Crosshair::render(sf::RenderWindow& renderWindow) {
	_sprite.setPosition(_position.x, _position.y);
	renderWindow.draw(_sprite);
}
