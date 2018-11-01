#pragma once

#include <memory>

#include "GameEventType.h"
#include "Projectile.h"
#include "ProjectileImpactEvent.h"

using namespace Shooter::Items::Weapons;

namespace Shooter {
	namespace World {
		namespace Events {
			struct GameEvent {
				GameEventType GameEventType;
				ProjectileImpactEvent ProjectileImpactEvent;
			};
		}
	}
}