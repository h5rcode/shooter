#pragma once

#include "IItem.h"

namespace Shooter {
	namespace World {
		namespace Events {
			struct PlayerPickedUpItemEvent {
				std::shared_ptr<IItem> Item;
			};
		}
	}
}