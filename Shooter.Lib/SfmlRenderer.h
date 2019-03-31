#pragma once

#include <SFML/Graphics.hpp>

#include "IGameSetRenderer.h"
#include "IGameState.h"
#include "INonPlayingCharacterRenderer.h"
#include "IPlayerRenderer.h"
#include "IProjectileRenderer.h"
#include "IRenderer.h"
#include "IResourceManager.h"

using namespace Shooter::Rendering::Renderers;

namespace Shooter {
	namespace Rendering {
		class SfmlRenderer : public IRenderer
		{
		public:
			SfmlRenderer(
				IGameSetRenderer& gameSetRenderer,
				IGameState& gameState,
				INonPlayingCharacterRenderer& npcRenderer,
				IPlayerRenderer& playerRenderer,
				IProjectileRenderer& projectileRenderer,
				sf::RenderWindow& window,
				IResourceManager& resourceManager);

		public:
			void render(sf::Time elapsedTime);

		private:
			void renderCrosshair();
			void renderHud();

		private:
			sf::Sprite _crosshairSprite;
			IGameSetRenderer& _gameSetRenderer;
			IGameState& _gameState;
			INonPlayingCharacterRenderer& _npcRenderer;
			IPlayerRenderer& _playerRenderer;
			IProjectileRenderer& _projectileRenderer;
			IResourceManager& _resourceManager;
			sf::RenderWindow& _window;
			sf::Font _font;
		};
	}
}