#pragma once

#include <memory>

#include "Projectile.h"
#include "ProjectileImpactEvent.h"

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