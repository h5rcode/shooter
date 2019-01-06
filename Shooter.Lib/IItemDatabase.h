#pragma once

#include <string>
#include <vector>

#include "ItemDescriptor.h"

namespace Shooter {
	namespace WorldDatabase {
		namespace Items {
			class IItemDatabase {
			public:
				virtual std::vector<std::string> getAllSoundFilenames() = 0;
				virtual ItemDescriptor* getItem(std::string& id) = 0;
			};
		}
	}
}