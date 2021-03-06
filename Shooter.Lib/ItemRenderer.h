#pragma once

#include <SFML/Graphics.hpp>

#include "IResourceManager.h"
#include "IItemDatabase.h"
#include "IItemRenderer.h"

using namespace Shooter::WorldDatabase::Items;

namespace Shooter {
	namespace Rendering {
		namespace Renderers {
			class ItemRenderer : public IItemRenderer {
			public:
				ItemRenderer(IItemDatabase& itemDatabase, sf::RenderWindow& renderWindow, IResourceManager& resourceManager);

			public:
				void render(IItem& item);

			private:
				IItemDatabase& _itemDatabase;
				sf::RenderWindow& _renderWindow;
				IResourceManager& _resourceManager;
			};
		}
	}
}