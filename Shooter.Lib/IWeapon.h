#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Projectile.h"
#include "Vector2.h"

class IWeapon {
public:
	virtual bool canAttack() const = 0;
	virtual std::vector<std::shared_ptr<Projectile>> fire(Vector2& initialPosition, Vector2& targetPosition) = 0;
	virtual std::string getDescription() = 0;
};