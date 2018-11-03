#pragma once

#include "ItemDescriptor.h"

namespace Shooter {
	namespace WorldDatabase {
		namespace Items {
			class IItemDatabase {
			public:
				virtual std::shared_ptr<ItemDescriptor> getItem(std::string& id) = 0;
			};
		}
	}
}