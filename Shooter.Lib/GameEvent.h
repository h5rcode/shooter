#pragma once

#include <memory>
#include "GameEventType.h"
#include "PlayerHurtEvent.h"
#include "PlayerPickedUpItemEvent.h"
#include "ProjectileImpactEvent.h"

using namespace Shooter::Items::Weapons;

namespace Shooter {
	namespace World {
		namespace Events {
			struct GameEvent {
				GameEventType Type;
				ProjectileImpactEvent ProjectileImpact;
				PlayerHurtEvent PlayerHurt;
				PlayerPickedUpItemEvent PlayerPickedUpItem;
			};
		}
	}
}