#pragma once

#include "IGameSet.h"

namespace Shooter {
	namespace Rendering {
		namespace Renderers {
			class IGameSetRenderer {
			public:
				virtual void render(IGameSet& gameSet) const = 0;
			};
		}
	}
}