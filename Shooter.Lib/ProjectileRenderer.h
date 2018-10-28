#pragma once

#include "IProjectileRenderer.h"

namespace Shooter {
	namespace Rendering {
		namespace Renderers {
			class ProjectileRenderer : public IProjectileRenderer {
			public:
				ProjectileRenderer(sf::RenderWindow& renderWindow, sf::Texture& texture);
			public:
				void render(Projectile& projectile);
			private:
				sf::RenderWindow& _renderWindow;
				sf::Sprite _sprite;
			};
		}
	}
}