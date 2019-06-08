#pragma once

#include <memory>

#include "FirearmDescriptor.h"
#include "WeaponType.h"

namespace Shooter {
	namespace WorldDatabase {
		namespace Items {
			struct WeaponDescriptor {
				WeaponType weaponType;
				std::shared_ptr<FirearmDescriptor> Firearm;
			};
		}
	}
}