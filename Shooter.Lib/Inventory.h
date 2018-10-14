#pragma once

#include <memory>
#include <vector>

#include "IItem.h"
#include "IInventory.h"

namespace Shooter {
	namespace Inventory {
		class Inventory : public IInventory
		{
		public:
			Inventory();
			Inventory(int maxWeight);

		public:
			bool addItem(std::shared_ptr<IItem> item);
			int getCurrentWeight() const;
			std::vector<std::shared_ptr<IItem>>& getItems();
			int getMaxWeight() const;

		private:
			std::vector<std::shared_ptr<IItem>> _items;

			int _currentWeight;
			int _maxWeight;
		};
	}
}