#pragma once

#include <map>
#include <string>

#include "IItemDatabase.h"
#include "ItemDescriptor.h"

namespace Shooter {
	namespace WorldDatabase {
		namespace Items {
			class ItemDatabase : public IItemDatabase {
			public:
				ItemDatabase(std::string fileName);

			public:
				std::vector<std::string> getAllSoundFilenames();
				ItemDescriptor& getItem(std::string& id);

			private:
				std::map<std::string, std::shared_ptr<ItemDescriptor>> _items;
			};
		}
	}
}