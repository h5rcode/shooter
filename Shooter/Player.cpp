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

Vector2 Player::computePosition(int elapsedMs)
{
	double elapsedS = (double)elapsedMs / 1000;

	Vector2 nextSpeed = computeSpeed(elapsedMs);
	Vector2 positionIncrement = multiply(nextSpeed, elapsedS);

	return _position + positionIncrement;
}

Vector2 Player::computeSpeed(int elapsedMs) {
	double elapsedS = (double)elapsedMs / 1000;

	Vector2 friction = multiply(_speed, -_friction);
	Vector2 speedIncrement = multiply(_acceleration + friction, elapsedS);

	Vector2 nextSpeed = _speed + speedIncrement;

	double speedNorm = nextSpeed.getNorm();
	if (speedNorm > _maxSpeed) {
		nextSpeed.normalize();
		multiply(nextSpeed, _maxSpeed);
	}
	else if (speedNorm <= MIN_SPEED) {
		nextSpeed.x = 0;
		nextSpeed.y = 0;
	}

	return nextSpeed;
}

Vector2& Player::getPosition() {
	return _position;
}

std::string& Player::getTexture() {
	return _texture;
}

void Player::move(int elapsedMs) {
	double elapsedS = (double)elapsedMs / 1000;

	Vector2 nextSpeed = computeSpeed(elapsedMs);
	Vector2 positionIncrement = multiply(nextSpeed, elapsedS);
	Vector2 nextPosition = _position + positionIncrement;

	_speed = nextSpeed;
	_position = nextPosition;
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
