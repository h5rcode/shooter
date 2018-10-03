#include "Player.h"

const double MIN_SPEED = 0.01;

const int FRAME_WIDTH = 64;
const int FRAME_HEIGHT = 64;
const int PLAYER_REACH = 64;
const int FRAME_TIME_MILLISECONDS = 150;

Player::Player(Vector2 position, int hitpoints, IAnimatedRenderable& animatedRenderable, IInventory& inventory) :
	_friction(5),
	_hitpoints(hitpoints),
	_inventory(inventory),
	_maxSpeed(10000),
	_position(position),
	_reach(PLAYER_REACH),
	_sound(),
	_soundBuffer(),
	_animatedRenderable(animatedRenderable)
{
	_soundBuffer.loadFromFile("Resources/sounds/138476__randomationpictures__step-tap.wav");
	_sound.setPlayingOffset(sf::milliseconds(2 * FRAME_TIME_MILLISECONDS));
	_sound.setBuffer(_soundBuffer);
	_sound.setLoop(true);
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

std::shared_ptr<Prop> Player::getProp() {
	return _prop;
}

bool Player::canAttack() const {
	return _equipedWeapon != NULL && _equipedWeapon->canAttack();
}

int Player::getHitpoints() const {
	return _hitpoints;
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

void Player::hurt(int damage) {
	_hitpoints -= damage;
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

std::shared_ptr<Prop> Player::dropProp() {
	std::shared_ptr<Prop> prop = _prop;
	_prop = NULL;
	return prop;
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
		_animatedRenderable.pause();
	}
	else {
		if (_sound.getStatus() != sf::Sound::Playing) {
			_sound.play();
		}

		_animatedRenderable.play();
		_animatedRenderable.update(elapsedTime);
	}
}

bool Player::pickUpItem(std::shared_ptr<IItem> item) {

	Vector2& itemPosition = item->getPosition();
	Vector2 positionDifference = _position - itemPosition;
	double distanceBetweenPlayerAndItem = positionDifference.getNorm();

	if (distanceBetweenPlayerAndItem > _reach) {
		return false;
	}

	return _inventory.addItem(item);
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
	_animatedRenderable.setRotation(_orientation);
	_animatedRenderable.setPosition(_position.x, _position.y);
	_animatedRenderable.render(renderWindow);
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
