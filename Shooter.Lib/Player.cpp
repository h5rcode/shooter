#include "Player.h"

using namespace Shooter::Inventory;
using namespace Shooter::Math;
using namespace Shooter::World;

const double MIN_SPEED = 1;

const int FRAME_WIDTH = 64;
const int FRAME_HEIGHT = 64;
const int PLAYER_REACH = 32;

Player::Player(
	Vector2 position,
	int hitpoints,
	IInventory& inventory) :
	_friction(20),
	_hitpoints(hitpoints),
	_inventory(inventory),
	_maxSpeed(200),
	_position(position),
	_reach(PLAYER_REACH)
{
}

std::vector<std::shared_ptr<Projectile>> Player::attackToward(Vector2& position) {
	std::vector<std::shared_ptr<Projectile>> projectiles;
	if (_equipedWeapon != NULL) {
		Vector2 projectileRelativeInitialPosition = Vector2(0, -_reach);
		projectileRelativeInitialPosition.rotate(_orientation);

		projectiles = _equipedWeapon->fire(_position + projectileRelativeInitialPosition, position);
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

int Player::getHitpoints() const {
	return _hitpoints;
}

IInventory& Player::getInventory() {
	return _inventory;
}

std::shared_ptr<IWeapon> Player::getEquipedWeapon() const {
	return _equipedWeapon;
}

double Player::getOrientation()
{
	return _orientation;
}

Vector2& Player::getSpeed()
{
	return _speed;
}

Segment Player::getTrajectory(sf::Time elapsedTime) {
	Vector2 nextPosition = computePosition(elapsedTime);

	return Segment(_position, nextPosition);
}

void Player::hurt(int damage) {
	_hitpoints -= damage;
}

void Player::immobilize() {
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

	Vector2 speedIncrement;
	if (_acceleration != Vector2(0, 0)) {
		speedIncrement = multiply(_acceleration, elapsedSeconds);
	}
	else {
		speedIncrement = multiply(_speed, -_friction * elapsedSeconds);
	}

	Vector2 nextSpeed = _speed + speedIncrement;

	double speedNorm = nextSpeed.getNorm();
	if (speedNorm > _maxSpeed) {
		nextSpeed.normalize();
		nextSpeed = multiply(nextSpeed, _maxSpeed);
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

void Player::pointAt(Vector2& position)
{
	_orientation = _position.computeAngleTo(position);
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
