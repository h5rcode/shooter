#pragma once

#include <string>

#include "ItemType.h"

namespace Shooter {
	namespace WorldDatabase {
		namespace Items {
			struct ItemDescriptor {
				virtual ~ItemDescriptor() {}

				std::string id;
				std::string name;
				std::string texture;
				int width;
				int height;
				int weight;

				ItemType itemType;
			};
		}
	}
}