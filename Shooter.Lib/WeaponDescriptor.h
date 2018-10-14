#pragma once

#include "FirearmDescriptor.h"
#include "WeaponType.h"

namespace Shooter {
	namespace ItemDatabase {
		struct WeaponDescriptor {
			WeaponType weaponType;

			union {
				FirearmDescriptor firearm;
			};
		};
	}
}