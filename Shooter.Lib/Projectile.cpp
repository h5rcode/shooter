#include "Projectile.h"

using namespace Shooter::Items::Weapons;
using namespace Shooter::Math;
using namespace Shooter::World;

Projectile::Projectile(Vector2 position, Vector2 speed, int damage) :
	_position(position),
	_speed(speed),
	_damage(damage),
	_width(8),
	_height(8)
{
	_orientation = _position.computeAngleTo(_position + speed);
}

BoundingBox Projectile::getBoundingBox(sf::Time elapsedTime) {
	Vector2 position = computePosition(elapsedTime);
	return BoundingBox(position, _width / 2, _height / 2, _orientation);
}

int Projectile::getDamage() const {
	return _damage;
}

int Projectile::getHeight() const {
	return _height;
}

double Projectile::getOrientation() const {
	return _orientation;
}

Vector2& Projectile::getPosition() {
	return _position;
}

int Projectile::getWidth() const {
	return _width;
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