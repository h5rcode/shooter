#pragma once

#include "IPlayer.h"

namespace Shooter {
	namespace Rendering {
		namespace Renderers {
			class IPlayerRenderer {
			public:
				virtual void render(IPlayer& player, sf::Time elapsedTime) = 0;
			};
		}
	}
}