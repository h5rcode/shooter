#pragma once

#include <SFML/Graphics.hpp>

#include "IInventory.h"

using namespace Shooter::Math;

namespace Shooter {
	namespace Npcs {
		class INonPlayingCharacter {
		public:
			virtual BoundingBox getBoundingBox(sf::Time elapsedTime) = 0;
			virtual int getHitPoints() = 0;
			virtual std::string& getId() = 0;
			virtual double getOrientation() = 0;
			virtual Vector2& getPosition() = 0;
			virtual void hurt(int damage) = 0;
		};
	}
}