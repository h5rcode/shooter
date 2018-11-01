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
			SfmlAudioSystem(IGameState& gameState, IResourceManager& resourceManager);
			~SfmlAudioSystem();
		public:
			void update();

		private:
			void deleteStoppedSounds();
			void playSound(std::string filename);

		private:
			IGameState& _gameState;
			IResourceManager& _resourceManager;
			std::vector<sf::Sound*> _sounds;
		};
	}
}