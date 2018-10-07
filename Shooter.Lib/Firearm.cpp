#include <sstream>

#include "Firearm.h"

Firearm::Firearm(
	std::string name,
	int capacity,
	int damage,
	double muzzleVelocity,
	int roundsPerMinute,
	int weight,
	Vector2 position,
	int width,
	int height,
	double orientation,
	IResourceManager&  resourceManager,
	std::shared_ptr<IStaticRenderable> staticRenderable)
	:
	AbstractItem(name, weight, position, width, height, orientation, staticRenderable),
	_capacity(capacity),
	_damage(damage),
	_projectileTexture((std::string&)"Resources/textures/bullet.png"),
	_muzzleVelocity(muzzleVelocity),
	_remainingRounds(capacity),
	_roundsPerMinute(roundsPerMinute),
	_timeBetweenTwoShots(sf::seconds(1.f / (roundsPerMinute / 60.f))),
	_timeSinceLastShot(),
	_resourceManager(resourceManager)
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

	sf::Texture* projectileTexture = _resourceManager.getTexture(_projectileTexture);

	std::shared_ptr<Projectile> projectile = std::make_shared<Projectile>(initialPosition, projectileSpeed, _damage, *projectileTexture);

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
