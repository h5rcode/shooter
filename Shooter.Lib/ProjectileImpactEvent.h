#pragma once

#include <memory>

#include "Projectile.h"

using namespace Shooter::Items::Weapons;

namespace Shooter {
	namespace World {
		namespace Events {
			struct ProjectileImpactEvent {
				std::shared_ptr<Projectile> Projectile;
			};
		}
	}
}