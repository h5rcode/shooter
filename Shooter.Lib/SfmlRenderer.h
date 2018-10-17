#pragma once

#include <SFML/Graphics.hpp>

#include "IGameState.h"
#include "IPlayerRenderer.h"
#include "IRenderer.h"
#include "IResourceManager.h"

using namespace Shooter::Rendering::Renderers;

namespace Shooter {
	namespace Rendering {
		class SfmlRenderer : public IRenderer
		{
		public:
			SfmlRenderer(
				IGameState& gameState,
				IPlayerRenderer& playerRenderer,
				sf::RenderWindow& window,
				IResourceManager& resourceManager);

		public:
			void render(sf::Time elapsedTime);

		private:
			void renderHud();

		private:
			IGameState& _gameState;
			IPlayerRenderer& _playerRenderer;
			IResourceManager& _resourceManager;
			sf::RenderWindow& _window;
			sf::Font _font;
		};
	}
}