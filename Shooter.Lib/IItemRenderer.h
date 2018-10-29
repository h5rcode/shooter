#pragma once

#include "IItem.h"

using namespace Shooter::Items;

namespace Shooter {
	namespace Rendering {
		namespace Renderers {
			class IItemRenderer {
			public:
				virtual void render(IItem& item) = 0;
			};
		}
	}
}