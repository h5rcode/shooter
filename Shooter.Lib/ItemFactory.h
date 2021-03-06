#pragma once

#include <memory>
#include <string>

#include "IItem.h"
#include "IItemDatabase.h"
#include "Vector2.h"

using namespace Shooter::WorldDatabase::Items;
using namespace Shooter::Math;

namespace Shooter {
	namespace Items {
		class ItemFactory
		{
		public:
			ItemFactory(IItemDatabase& itemDatabase);

		public:
			std::shared_ptr<IItem> buildItem(std::string itemId, Vector2& position, double orientation);

		private:
			IItemDatabase& _itemDatabase;
		};
	}
}