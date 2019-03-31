#include "NonPlayingCharacter.h"

using namespace Shooter::Npcs;

NonPlayingCharacter::NonPlayingCharacter(
	std::string id,
	double orientation,
	Vector2 position,
	int hitPoints,
	int width,
	int height) :
	_id(id),
	_orientation(orientation),
	_position(position),
	_hitPoints(hitPoints),
	_width(width),
	_height(height) {}

BoundingBox NonPlayingCharacter::getBoundingBox(sf::Time elapsedTime)
{
	return BoundingBox(_position, _width / 2, _height / 2, _orientation);
}

int NonPlayingCharacter::getHitPoints() {
	return _hitPoints;
}

std::string& NonPlayingCharacter::getId() {
	return _id;
}

double NonPlayingCharacter::getOrientation() {
	return _orientation;
}

Vector2& NonPlayingCharacter::getPosition() {
	return _position;
}

void NonPlayingCharacter::hurt(int damage) {
	_hitPoints -= damage;
}