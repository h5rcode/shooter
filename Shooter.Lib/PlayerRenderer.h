#pragma once

#include <SFML/Graphics.hpp>

#include "AnimatedSprite.h"
#include "IPlayer.h"
#include "IPlayerRenderer.h"
#include "RenderingOptions.h"

using namespace Shooter::Rendering;

namespace Shooter {
	namespace Rendering {
		namespace Renderers {
			class PlayerRenderer : public IPlayerRenderer {
			public:
				PlayerRenderer(RenderingOptions& renderingOptions, sf::RenderWindow& renderWindow, sf::Texture& texture);
			public:
				void render(IPlayer& player, sf::Time elapsedTime);

			private:
				Animation _animation;
				AnimatedSprite _animatedSprite;
				RenderingOptions& _renderingOptions;
				sf::RenderWindow& _renderWindow;
			};
		}
	}
}