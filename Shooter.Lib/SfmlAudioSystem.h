#pragma once

#include <SFML/Audio.hpp>

#include "IAudioSystem.h"
#include "IGameState.h"
#include "IItemDatabase.h"
#include "IResourceManager.h"

using namespace Shooter::Rendering;
using namespace Shooter::WorldDatabase::Items;

namespace Shooter {
	namespace Audio {
		class SfmlAudioSystem : public IAudioSystem {
		public:
			SfmlAudioSystem(
				IGameState& gameState,
				IItemDatabase& itemDatabase,
				sf::RenderWindow& renderWindow,
				IResourceManager& resourceManager);
			~SfmlAudioSystem();
		public:
			void update(std::vector<GameEvent>& gameEvents);

		private:
			void deleteStoppedSounds();
			void playSound(std::string filename, Vector2 position, bool relativeToListener, bool loop = false);

		private:
			IGameState& _gameState;
			IItemDatabase& _itemDatabase;
			sf::RenderWindow& _renderWindow;
			IResourceManager& _resourceManager;
			std::vector<sf::Sound*> _sounds;
			sf::Sound _playerFootstepsSound;
		};
	}
}