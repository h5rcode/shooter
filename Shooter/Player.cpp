#include "Player.h"

const double MIN_SPEED = 0.01;

Player::Player(std::string& texture) :
	_friction(5),
	_maxSpeed(10000),
	_texture(texture)
{
}

bool Player::canAttack() const {
	return _state == IDLE;
}

IWeapon* Player::getEquipedWeapon() const {
	return _equipedWeapon;
}

double Player::getOrientation()
{
	return _orientation;
}

Vector2& Player::getPosition() {
	return _position;
}

std::string& Player::getTexture() {
	return _texture;
}

void Player::move(int elapsedMs) {
	double elapsedS = (double)elapsedMs / 1000;

	Vector2 friction = multiply(_speed, -_friction);
	Vector2 speedIncrement = multiply(_acceleration + friction, elapsedS);

	_speed += speedIncrement;

	double speedNorm = _speed.getNorm();
	if (speedNorm > _maxSpeed) {
		_speed.normalize();
		multiply(_speed, _maxSpeed);
	}
	else if (speedNorm <= MIN_SPEED) {
		_speed.x = 0;
		_speed.y = 0;
	}

	Vector2 positionIncrement = multiply(_speed, elapsedS);
	_position += positionIncrement;
}

void Player::pointAt(Vector2& position)
{
	_orientation = _position.computeAngleTo(position);
}

void Player::setAcceleration(Vector2& acceleration) {
	_acceleration.x = acceleration.x;
	_acceleration.y = acceleration.y;
}

void Player::setEquipedWeapon(IWeapon* weapon) {
	_equipedWeapon = weapon;
}

void Player::setMaxSpeed(double maxSpeed) {
	_maxSpeed = maxSpeed;
}
