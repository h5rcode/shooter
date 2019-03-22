#pragma once

#include "Floor.h"

using namespace Shooter::World;

namespace Shooter {
	namespace Rendering {
		namespace Renderers {
			class IFloorRenderer {
			public:
				virtual void render(Floor& wall) = 0;
			};
		}
	}
}