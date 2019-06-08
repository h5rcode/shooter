#pragma once

#include <memory>
#include <string>

#include "BoundingBox.h"
#include "IItem.h"
#include "IPlayer.h"
#include "IWeapon.h"
#include "Vector2.h"

using namespace Shooter::Inventory;
using namespace Shooter::Math;

namespace Shooter {
	namespace World {
		typedef enum CharacterState {
			IDLE,
			ATTACKING
		} CharacterState;

		class Player : public IPlayer
		{
		public:
			Player(
				Vector2 position,
				int hitpoints,
				IInventory& inventory);

		public:
			std::vector<std::shared_ptr<Projectile>> attackToward(Vector2& position);
			bool canAttack() const;
			void collide(Vector2& collisionNormal);
			Vector2 computePosition(sf::Time elapsedTime);
			void equipWeapon(std::shared_ptr<IWeapon> weapon);
			BoundingBox getBoundingBox(sf::Time elapsedTime);
			std::shared_ptr<IWeapon> getEquipedWeapon() const;
			int getHitpoints() const;
			IInventory& getInventory();
			double getOrientation();
			Vector2& getPosition();
			Vector2& getSpeed();
			void hurt(int damage);
			void immobilize();
			void move(sf::Time elapsedTime);
			bool pickUpItem(std::shared_ptr<IItem> item);
			void pointAt(Vector2& position);
			void setAcceleration(Vector2& acceleration);
			void setEquipedWeapon(std::shared_ptr<IWeapon> weapon);
			void setMaxSpeed(double maxSpeed);
			void updateSpeed(sf::Time elapsedTime);

		private:
			double _friction;
			int _hitpoints;
			double _maxSpeed;
			double _reach;
			Vector2 _acceleration;
			Vector2 _speed;
			Vector2 _position;
			double _orientation;

			std::shared_ptr<IWeapon> _equipedWeapon;

			IInventory& _inventory;

			CharacterState _state;
		};
	}
}