#include "Animation.h"
#include "Player.h"

const double MIN_SPEED = 0.01;

const int FRAME_WIDTH = 64;
const int FRAME_HEIGHT = 64;
const int PLAYER_REACH = 64;
const int NUMBER_OF_FRAMES = 8;
const int FRAME_TIME_MILLISECONDS = 150;

Player::Player(Vector2 position) :
	_animatedSprite(),
	_animation(),
	_friction(5),
	_maxSpeed(10000),
	_position(position),
	_reach(PLAYER_REACH),
	_sound(),
	_soundBuffer(),
	_texture()
{
	_soundBuffer.loadFromFile("Resources/sounds/138476__randomationpictures__step-tap.wav");
	_sound.setPlayingOffset(sf::milliseconds(2 * FRAME_TIME_MILLISECONDS));
	_sound.setBuffer(_soundBuffer);
	_sound.setLoop(true);

	_texture.loadFromFile("Resources/textures/character.png");

	_animation.setSpriteSheet(_texture);
	for (int frameNumber = 0; frameNumber < NUMBER_OF_FRAMES; frameNumber++) {
		_animation.addFrame(sf::IntRect(0, frameNumber * FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT));
	}

	_animatedSprite.setAnimation(_animation);
	_animatedSprite.setOrigin(FRAME_WIDTH / 2, FRAME_HEIGHT / 2);
	_animatedSprite.setFrameTime(sf::milliseconds(FRAME_TIME_MILLISECONDS));
}

std::vector<std::shared_ptr<Projectile>> Player::attackToward(Vector2& position) {
	std::vector<std::shared_ptr<Projectile>> projectiles;
	if (_equipedWeapon != NULL) {
		projectiles = _equipedWeapon->fire(_position, position);
	}

	return projectiles;
}

void Player::equipWeapon(std::shared_ptr<IWeapon> weapon) {
	_equipedWeapon = weapon;
}

BoundingBox Player::getBoundingBox(sf::Time elapsedTime)
{
	Vector2 position = computePosition(elapsedTime);
	return BoundingBox(position, FRAME_WIDTH / 2, FRAME_HEIGHT / 2, _orientation);
}

bool Player::canAttack() const {
	return _equipedWeapon != NULL && _equipedWeapon->canAttack();
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

void Player::immobilize() {
	if (_sound.getStatus() == sf::Sound::Playing) {
		_sound.pause();
	}

	_acceleration = Vector2();
	_speed = Vector2();
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
		_sound.pause();
		_animatedSprite.pause();
	}
	else {
		if (_sound.getStatus() != sf::Sound::Playing) {
			_sound.play();
		}

		_animatedSprite.play();
		_animatedSprite.update(elapsedTime);
	}
}

bool Player::pickUpProp(std::shared_ptr<Prop> prop) {
	bool propWasPickedUp = false;

	if (_prop == NULL) {
		Vector2& propPosition = prop->getPosition();
		Vector2 positionDifference = _position - propPosition;
		double distanceBetweenPlayerAndProp = positionDifference.getNorm();

		if (distanceBetweenPlayerAndProp <= _reach) {
			_prop = prop;
			propWasPickedUp = true;
		}
	}

	return propWasPickedUp;
}

void Player::pointAt(Vector2& position)
{
	_orientation = _position.computeAngleTo(position);
}

void Player::render(sf::RenderWindow& renderWindow) {
	_animatedSprite.setRotation((float)_orientation);
	_animatedSprite.setPosition((float)_position.x, (float)_position.y);
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
