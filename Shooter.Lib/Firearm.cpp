#include <sstream>

#include "Firearm.h"

using namespace Shooter::Items::Weapons;
using namespace Shooter::Math;

Firearm::Firearm(
	std::string id,
	std::string name,
	int capacity,
	int damage,
	double muzzleVelocity,
	int roundsPerMinute,
	int weight,
	Vector2 position,
	int width,
	int height,
	double orientation)
	:
	AbstractItem(id, name, weight, position, width, height, orientation),
	_capacity(capacity),
	_damage(damage),
	_muzzleVelocity(muzzleVelocity),
	_remainingRounds(capacity),
	_roundsPerMinute(roundsPerMinute),
	_timeBetweenTwoShots(sf::seconds(1.f / (roundsPerMinute / 60.f))),
	_timeSinceLastShot()
{
}

bool Firearm::canAttack() const
{
	if (_remainingRounds < 1) {
		return false;
	}

	sf::Time ellapsedTimeSinceLastShot = _timeSinceLastShot.getElapsedTime();
	return ellapsedTimeSinceLastShot >= _timeBetweenTwoShots;
}

std::vector<std::shared_ptr<Projectile>> Firearm::fire(Vector2& initialPosition, Vector2& targetPosition)
{
	Vector2 projectileDirection = targetPosition - initialPosition;
	projectileDirection.normalize();

	Vector2 projectileSpeed = multiply(projectileDirection, _muzzleVelocity);

	std::shared_ptr<Projectile> projectile = std::make_shared<Projectile>(initialPosition, projectileSpeed, _damage);

	std::vector<std::shared_ptr<Projectile>> projectiles;
	projectiles.push_back(projectile);

	_timeSinceLastShot.restart();
	_remainingRounds--;

	return projectiles;
}

std::string Firearm::getDescription() {
	std::stringstream stream;
	stream << _remainingRounds << " / " << _capacity;
	return stream.str();
}
