#pragma once

#include "FirearmDescriptor.h"
#include "WeaponType.h"

namespace Shooter {
	namespace WorldDatabase {
		namespace Items {
			struct WeaponDescriptor {
				WeaponType weaponType;

				union {
					FirearmDescriptor firearm;
				};
			};
		}
	}
}