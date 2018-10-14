#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "AbstractItem.h"
#include "IResourceManager.h"
#include "IStaticRenderable.h"
#include "IWeapon.h"
#include "Projectile.h"
#include "Vector2.h"

namespace Shooter {
	namespace Items {
		namespace Weapons {

			class Firearm : public AbstractItem, public IWeapon {
			public:
				Firearm(
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
					IResourceManager& resourceManager,
					std::shared_ptr<IStaticRenderable> staticRenderable);

			public:
				bool canAttack() const;
				std::vector<std::shared_ptr<Projectile>> fire(Vector2& initialPosition, Vector2& targetPosition);
				std::string getDescription();

			public:
				int _capacity;
				int _damage;
				std::string& _projectileTexture;
				double _muzzleVelocity;
				int _remainingRounds;
				int _roundsPerMinute;
				sf::Time _timeBetweenTwoShots;
				sf::Clock _timeSinceLastShot;

				IResourceManager& _resourceManager;
			};
		}
	}
}