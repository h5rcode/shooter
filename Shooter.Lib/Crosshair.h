#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include "Vector2.h"

using namespace Shooter::Math;

namespace Shooter {
	namespace World {
		class Crosshair
		{
		public:
			Crosshair(sf::Texture& texture);

			Vector2& getPosition();

			void render(sf::RenderWindow& renderWindow);

		private:
			sf::Sprite _sprite;

			Vector2 _position;
		};
	}
}

