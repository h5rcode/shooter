#pragma once

#include <memory>

#include "BoundingBox.h"
#include "IInventory.h"
#include "IItem.h"
#include "IWeapon.h"
#include "Prop.h"
#include "Vector2.h"

using namespace Shooter::Inventory;
using namespace Shooter::Items::Weapons;
using namespace Shooter::Math;

namespace Shooter {
	namespace World {
		class IPlayer {
		public:
			virtual std::vector<std::shared_ptr<Projectile>> attackToward(Vector2& position) = 0;
			virtual bool canAttack() const = 0;
			virtual Vector2 computePosition(sf::Time elapsedTime) = 0;
			virtual std::shared_ptr<Prop> dropProp() = 0;
			virtual void equipWeapon(std::shared_ptr<IWeapon> weapon) = 0;
			virtual BoundingBox getBoundingBox(sf::Time elapsedTime) = 0;
			virtual std::shared_ptr<IWeapon> getEquipedWeapon() const = 0;
			virtual int getHitpoints() const = 0;
			virtual IInventory& getInventory() = 0;
			virtual double getOrientation() = 0;
			virtual Vector2& getPosition() = 0;
			virtual std::shared_ptr<Prop> getProp() = 0;
			virtual Vector2& getSpeed() = 0;
			virtual void hurt(int damage) = 0;
			virtual void immobilize() = 0;
			virtual void move(sf::Time elapsedTime) = 0;
			virtual bool pickUpItem(std::shared_ptr<IItem> item) = 0;
			virtual bool pickUpProp(std::shared_ptr<Prop> prop) = 0;
			virtual void pointAt(Vector2& position) = 0;
			virtual void setAcceleration(Vector2& acceleration) = 0;
			virtual void setEquipedWeapon(std::shared_ptr<IWeapon> weapon) = 0;
			virtual void setMaxSpeed(double maxSpeed) = 0;
		};
	}
}