#pragma once

#include <string>

#include "ItemType.h"
#include "WeaponDescriptor.h"

namespace Shooter {
	namespace ItemDatabase {
		struct ItemDescriptor {
			std::string id;
			std::string name;
			std::string texture;
			int width;
			int height;
			int weight;

			ItemType itemType;
			union {
				WeaponDescriptor weapon;
			};
		};
	}
}