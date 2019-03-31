#pragma once

#include "INonPlayingCharacter.h"

using namespace Shooter::Math;

namespace Shooter {
	namespace Npcs {
		class NonPlayingCharacter : public INonPlayingCharacter {
		public:
			NonPlayingCharacter(
				std::string id,
				double orientation,
				Vector2 position,
				int hitPoints,
				int width,
				int height);

			BoundingBox getBoundingBox(sf::Time elapsedTime);
			int getHitPoints();
			std::string& getId();
			double getOrientation();
			Vector2& getPosition();
			void hurt(int damage);

		private:
			Vector2 computeSpeed(sf::Time elapsedTime);

		private:
			std::string _id;
			int _hitPoints;
			double _orientation;
			Vector2 _position;
			int _width;
			int _height;
		};
	}
}