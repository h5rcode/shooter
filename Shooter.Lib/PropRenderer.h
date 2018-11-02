#pragma once

#include <SFML/Graphics.hpp>

#include "IPropDatabase.h"
#include "IPropRenderer.h"
#include "IResourceManager.h"

using namespace Shooter::WorldDatabase::Props;
using namespace Shooter::Rendering;

namespace Shooter {
	namespace Rendering {
		namespace Renderers {
			class PropRenderer : public IPropRenderer {
			public:
				PropRenderer(IPropDatabase& propDatabase, sf::RenderWindow& renderWindow, IResourceManager& resourceManager);
			public:
				void render(Prop& prop);
			private:
				IPropDatabase& _propDatabase;
				sf::RenderWindow& _renderWindow;
				IResourceManager& _resourceManager;
			};
		}
	}
}