#pragma once

#include <SFML/Graphics.hpp>

#include "INonPlayingCharacterDatabase.h"
#include "INonPlayingCharacterRenderer.h"
#include "IResourceManager.h"

using namespace Shooter::Rendering;
using namespace Shooter::Rendering::Renderers;
using namespace Shooter::WorldDatabase::Npcs;

namespace Shooter {
	namespace Rendering {
		namespace Renderers {
			class NonPlayingCharacterRenderer : public INonPlayingCharacterRenderer {
			public:
				NonPlayingCharacterRenderer(
					INonPlayingCharacterDatabase& npcDatabase,
					sf::RenderWindow& renderWindow,
					IResourceManager& resourceManager);
				void render(INonPlayingCharacter& npc);

			private:
				INonPlayingCharacterDatabase& _npcDatabase;
				sf::RenderWindow& _renderWindow;
				IResourceManager& _resourceManager;
				sf::Sprite _sprite;
			};
		}
	}
}