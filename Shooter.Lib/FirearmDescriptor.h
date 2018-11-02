#pragma once

namespace Shooter {
	namespace WorldDatabase {
		namespace Items {
			struct FirearmDescriptor {
				int capacity;
				int damage;
				double muzzleVelocity;
				int roundsPerMinute;
			};
		}
	}
}