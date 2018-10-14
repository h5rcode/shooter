#pragma once

#include "ItemDescriptor.h"

namespace Shooter {
	namespace ItemDatabase {
		class IItemDatabase {
		public:
			virtual ItemDescriptor& getItem(std::string& id) = 0;
		};
	}
}