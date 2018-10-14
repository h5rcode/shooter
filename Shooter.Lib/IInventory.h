#pragma once

#include "IItem.h"

using namespace Shooter::Items;

namespace Shooter {
	namespace Inventory {
		class IInventory {

		public:
			virtual bool addItem(std::shared_ptr<IItem> item) = 0;
			virtual int getCurrentWeight() const = 0;
			virtual std::vector<std::shared_ptr<IItem>>& getItems() = 0;
			virtual int getMaxWeight() const = 0;
		};
	}
}