#pragma once

#include "IItem.h"

using namespace Shooter::Items;

namespace Shooter {
	namespace World {
		namespace Events {
			struct PlayerPickedUpItemEvent {
				std::shared_ptr<IItem> Item;
			};
		}
	}
}