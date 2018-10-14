#include "Projectile.h"

using namespace Shooter::Items::Weapons;
using namespace Shooter::Math;
using namespace Shooter::World;

Projectile::Projectile(Vector2 position, Vector2 speed, int damage, sf::Texture& texture) :
	_position(position),
	_speed(speed),
	_damage(damage),
	_width(8),
	_height(8),
	_sprite()
{
	_orientation = _position.computeAngleTo(_position + speed);

	_sprite.setTexture(texture);
	_sprite.setTextureRect(sf::IntRect(0, 0, _width, _height));
	_sprite.setOrigin(_width / 2.f, _height / 2.f);
}

BoundingBox Projectile::getBoundingBox(sf::Time elapsedTime) {
	Vector2 position = computePosition(elapsedTime);
	return BoundingBox(position, _width / 2, _height / 2, _orientation);
}

int Projectile::getDamage() const {
	return _damage;
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