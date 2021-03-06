#pragma once

#include <SFML/Graphics.hpp>

#include "BoundingBox.h"
#include "Vector2.h"

using namespace Shooter::Math;
using namespace Shooter::World;

namespace Shooter {
	namespace Items {
		namespace Weapons {
			class Projectile {
			public:
				Projectile(Vector2 position, Vector2 speed, int damage);

			public:
				Vector2 computePosition(sf::Time elapsedTime);
				BoundingBox getBoundingBox(sf::Time elapsedTime);
				int getDamage() const;
				int getHeight() const;
				double getOrientation() const;
				Vector2& getPosition();
				int getWidth() const;
				void move(sf::Time elapsedTime);

			public:
				int _damage;
				double _orientation;
				Vector2 _position;
				Vector2 _speed;
				int _width;
				int _height;
			};
		}
	}
}