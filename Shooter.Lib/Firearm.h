#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "AbstractItem.h"
#include "IStaticRenderable.h"
#include "IWeapon.h"
#include "Projectile.h"
#include "Vector2.h"

class Firearm : public AbstractItem, public IWeapon {
public:
	Firearm(
		int capacity,
		int damage,
		double muzzleVelocity,
		int roundsPerMinute,
		int weight,
		Vector2 position,
		int width,
		int height,
		double orientation,
		std::shared_ptr<IStaticRenderable> staticRenderable);

public:
	bool canAttack() const;
	std::vector<std::shared_ptr<Projectile>> fire(Vector2& initialPosition, Vector2& targetPosition);
	std::string getDescription();

public:
	int _capacity;
	int _damage;
	double _muzzleVelocity;
	int _remainingRounds;
	int _roundsPerMinute;
	sf::Time _timeBetweenTwoShots;
	sf::Clock _timeSinceLastShot;
};