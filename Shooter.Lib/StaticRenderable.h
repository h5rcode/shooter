#pragma once

#include <SFML/Graphics.hpp>

#include "IStaticRenderable.h"
#include "Vector2.h"

using namespace Shooter::Math;

namespace Shooter {
	namespace Rendering {
		namespace Renderables {
			class StaticRenderable : public IStaticRenderable {
			public:
				StaticRenderable(
					Vector2 position,
					int width,
					int height,
					double orientation,
					sf::Texture& texture);

			public:
				void render(sf::RenderWindow& renderWindow) override;

			private:
				int _width;
				int _height;
				Vector2 _position;
				double _orientation;
				sf::Sprite _sprite;
			};
		}
	}
}