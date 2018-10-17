#pragma once

#include <SFML/Graphics.hpp>

namespace Shooter {
	namespace Rendering {
		class IRenderer {

		public:
			virtual void render(sf::Time elapsedTime) = 0;
		};
	}
}