#include <sstream>

#include "Firearm.h"

Firearm::Firearm(int capacity, int damage, double muzzleVelocity, int roundsPerMinute) :
	_capacity(capacity),
	_damage(damage),
	_muzzleVelocity(muzzleVelocity),
	_remainingRounds(capacity),
	_roundsPerMinute(roundsPerMinute),
	_timeBetweenTwoShots(sf::seconds(1.f / (roundsPerMinute / 60.f))),
	_timeSinceLastShot() {
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

	std::vector<std::shared_ptr<Projectile>> projectiles;
	_timeSinceLastShot.restart();
	std::shared_ptr<Projectile> projectile = std::make_shared<Projectile>(initialPosition, projectileSpeed, _damage);
	projectiles.push_back(projectile);
	_remainingRounds--;

	return projectiles;
}

std::string Firearm::getDescription() {
	std::stringstream stream;
	stream << _remainingRounds << " / " << _capacity;
	return stream.str();
}
