#pragma once

#include <string>

#include "WeaponDescriptor.h"

namespace Shooter {
	namespace WorldDatabase {
		namespace Items {
			struct FirearmDescriptor : public WeaponDescriptor {
				int capacity;
				int damage;
				double muzzleVelocity;
				int roundsPerMinute;
				std::string gunshotSound;
			};
		}
	}
}