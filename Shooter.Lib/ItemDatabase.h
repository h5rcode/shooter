#pragma once

#include <map>
#include <string>

#include "IItemDatabase.h"
#include "ItemDescriptor.h"
#include "WeaponDescriptor.h"

namespace Shooter {
	namespace WorldDatabase {
		namespace Items {
			class ItemDatabase : public IItemDatabase {
			public:
				ItemDatabase(std::string fileName);

			public:
				std::shared_ptr<ItemDescriptor> getItem(std::string& id);

			private:
				std::map<std::string, std::shared_ptr<ItemDescriptor>> _items;
			};
		}
	}
}