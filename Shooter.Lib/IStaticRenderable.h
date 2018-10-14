#pragma once

#include <SFML/Graphics.hpp>

namespace Shooter {
	namespace Rendering {
		namespace Renderables {
			class IStaticRenderable {
			public:
				virtual void render(sf::RenderWindow& renderWindow) = 0;
			};
		}
	}
}