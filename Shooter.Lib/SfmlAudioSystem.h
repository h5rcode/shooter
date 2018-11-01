#pragma once

#include <SFML/Audio.hpp>

#include "IAudioSystem.h"
#include "IGameState.h"
#include "IResourceManager.h"

using namespace Shooter::Rendering;

namespace Shooter {
	namespace Audio {
		class SfmlAudioSystem : public IAudioSystem {
		public:
			SfmlAudioSystem(IGameState& gameState, sf::RenderWindow& renderWindow, IResourceManager& resourceManager);
			~SfmlAudioSystem();
		public:
			void update();

		private:
			void deleteStoppedSounds();
			void playSound(std::string filename, Vector2 position, bool relativeToListener, bool loop = false);

		private:
			IGameState& _gameState;
			sf::RenderWindow& _renderWindow;
			IResourceManager& _resourceManager;
			std::vector<sf::Sound*> _sounds;
			sf::Sound _playerFootstepsSound;
		};
	}
}