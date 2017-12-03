#include "Animation.h"
#include "Player.h"

const double MIN_SPEED = 0.01;

const int FRAME_WIDTH = 64;
const int FRAME_HEIGHT = 64;
const int NUMBER_OF_FRAMES = 8;

Player::Player() :
	_friction(5),
	_maxSpeed(10000),
	_texture(),
	_animation(),
	_animatedSprite()
{
	_texture.loadFromFile("Resources/textures/character.png");

	_animation.setSpriteSheet(_texture);
	for (int frameNumber = 0; frameNumber < NUMBER_OF_FRAMES; frameNumber++) {
		_animation.addFrame(sf::IntRect(0, frameNumber * FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT));
	}

	_animatedSprite.setAnimation(_animation);
	_animatedSprite.setOrigin(FRAME_WIDTH / 2, FRAME_HEIGHT / 2);
}

BoundingBox Player::getBoundingBox(sf::Time elapsedTime)
{
	Vector2 position = computePosition(elapsedTime);
	return BoundingBox(position, FRAME_WIDTH, FRAME_HEIGHT, _orientation);
}

bool Player::canAttack() const {
	return _state == IDLE;
}

std::shared_ptr<IWeapon> Player::getEquipedWeapon() const {
	return _equipedWeapon;
}

double Player::getOrientation()
{
	return _orientation;
}

const Vector2& Player::getSpeed()
{
	return _speed;
}

Vector2 Player::computePosition(sf::Time elapsedTime)
{
	Vector2 nextSpeed = computeSpeed(elapsedTime);
	Vector2 positionIncrement = multiply(nextSpeed, elapsedTime.asSeconds());

	return _position + positionIncrement;
}

Vector2 Player::computeSpeed(sf::Time elapsedTime) {
	double elapsedSeconds = elapsedTime.asSeconds();

	Vector2 friction = multiply(_speed, -_friction);
	Vector2 speedIncrement = multiply(_acceleration + friction, elapsedSeconds);

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

void Player::move(sf::Time elapsedTime) {
	double elapsedSeconds = elapsedTime.asSeconds();

	Vector2 nextSpeed = computeSpeed(elapsedTime);
	Vector2 positionIncrement = multiply(nextSpeed, elapsedSeconds);
	Vector2 nextPosition = _position + positionIncrement;

	_speed = nextSpeed;
	_position = nextPosition;

	if (nextSpeed == Vector2(0, 0)) {
		_animatedSprite.pause();
	}
	else {
		_animatedSprite.play();
		_animatedSprite.update(elapsedTime);
	}
}

void Player::pointAt(Vector2& position)
{
	_orientation = _position.computeAngleTo(position);
}

void Player::render(sf::RenderWindow& renderWindow) {
	_animatedSprite.setRotation(_orientation);
	_animatedSprite.setPosition(_position.x, _position.y);
	renderWindow.draw(_animatedSprite);
}

void Player::setAcceleration(Vector2& acceleration) {
	_acceleration.x = acceleration.x;
	_acceleration.y = acceleration.y;
}

void Player::setEquipedWeapon(std::shared_ptr<IWeapon> weapon) {
	_equipedWeapon = weapon;
}

void Player::setMaxSpeed(double maxSpeed) {
	_maxSpeed = maxSpeed;
}