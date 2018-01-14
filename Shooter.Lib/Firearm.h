#pragma once

#include <SFML/Graphics.hpp>

#include "IWeapon.h"
#include "Projectile.h"
#include "Vector2.h"

class Firearm : public IWeapon {
public:
	Firearm(int capacity, int damage, double muzzleVelocity, int roundsPerMinute);

public:
	bool canAttack() const;
	std::vector<std::shared_ptr<Projectile>> fire(Vector2& initialPosition, Vector2& targetPosition);
	std::string getDescription();

public:
	int _capacity;
	int _damage;
	double _muzzleVelocity;
	double _orientation;
	int _remainingRounds;
	int _roundsPerMinute;
	sf::Time _timeBetweenTwoShots;
	sf::Clock _timeSinceLastShot;
};