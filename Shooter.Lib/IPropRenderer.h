#pragma once

#include "Prop.h"

using namespace Shooter::World;

namespace Shooter {
	namespace Rendering {
		namespace Renderers {
			class IPropRenderer {
			public:
				virtual void render(Prop& prop) = 0;
			};
		}
	}
}