#pragma once

#include <SFML/Graphics.hpp>

#include "IPropRenderer.h"
#include "IResourceManager.h"

using namespace Shooter::Rendering;

namespace Shooter {
	namespace Rendering {
		namespace Renderers {
			class PropRenderer : public IPropRenderer {
			public:
				PropRenderer(sf::RenderWindow& renderWindow, IResourceManager& resourceManager);
			public:
				void render(Prop& prop);
			private:
				sf::RenderWindow& _renderWindow;
				IResourceManager& _resourceManager;
			};
		}
	}
}