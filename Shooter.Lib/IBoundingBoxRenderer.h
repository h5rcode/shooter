#pragma once

#include "BoundingBox.h"

using namespace Shooter::World;

namespace Shooter {
	namespace Rendering {
		namespace Renderers {
			class IBoundingBoxRenderer {
			public:
				virtual void render(BoundingBox& boundingBox) = 0;
			};
		}
	}
}