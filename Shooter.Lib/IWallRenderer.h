#pragma once

#include "Wall.h"

using namespace Shooter::World;

namespace Shooter {
	namespace Rendering {
		namespace Renderers {
			class IWallRenderer {
			public:
				virtual void render(Wall& wall) = 0;
			};
		}
	}
}