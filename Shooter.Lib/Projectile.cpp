#include "Projectile.h"

Projectile::Projectile(Vector2 position, Vector2 speed, int damage) :
	_position(position),
	_speed(speed),
	_damage(damage),
	_width(8),
	_height(8),
	_texture(),
	_sprite()
{
	_orientation = _position.computeAngleTo(_position + speed);

	_texture.loadFromFile("Resources/textures/bullet.png");

	_sprite.setTexture(_texture);
	_sprite.setTextureRect(sf::IntRect(0, 0, _width, _height));
	_sprite.setOrigin(_width / 2.f, _height / 2.f);
}

BoundingBox Projectile::getBoundingBox(sf::Time elapsedTime) {
	Vector2 position = computePosition(elapsedTime);
	return BoundingBox(position, _width / 2, _height / 2, _orientation);
}

void Projectile::render(sf::RenderWindow& renderWindow) {
	_sprite.setPosition((float)_position.x, (float)_position.y);
	_sprite.setRotation((float)_orientation);
	renderWindow.draw(_sprite);
}

void Projectile::move(sf::Time elapsedTime) {
	Vector2 nextPosition = computePosition(elapsedTime);
	_position = nextPosition;
}

Vector2 Projectile::computePosition(sf::Time elapsedTime) {
	double elapsedSeconds = elapsedTime.asSeconds();

	Vector2 positionIncrement = multiply(_speed, elapsedSeconds);
	return _position += positionIncrement;
}