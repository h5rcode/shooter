#pragma once

#include "ItemDescriptor.h"
#include "WeaponType.h"

namespace Shooter {
	namespace WorldDatabase {
		namespace Items {
			struct WeaponDescriptor : public ItemDescriptor {
				WeaponType weaponType;
			};
		}
	}
}