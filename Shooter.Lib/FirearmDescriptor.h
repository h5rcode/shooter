#pragma once

namespace Shooter {
	namespace ItemDatabase {
		struct FirearmDescriptor {
			int capacity;
			int damage;
			double muzzleVelocity;
			int roundsPerMinute;
		};
	}
}