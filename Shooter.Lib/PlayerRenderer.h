#pragma once

#include "AnimatedSprite.h"
#include "IPlayer.h"
#include "IPlayerRenderer.h"

namespace Shooter {
	namespace Rendering {
		namespace Renderers {
			class PlayerRenderer : public IPlayerRenderer {
			public:
				PlayerRenderer(sf::RenderWindow& renderWindow, sf::Texture& texture);
			public:
				void render(IPlayer& player, sf::Time elapsedTime);

			private:
				Animation _animation;
				AnimatedSprite _animatedSprite;
				sf::RenderWindow& _renderWindow;
			};
		}
	}
}