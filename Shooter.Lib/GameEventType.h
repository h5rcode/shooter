#pragma once

namespace Shooter {
	namespace World {
		namespace Events {
			enum GameEventType {
				PlayerAttacked,
				PlayerHurt,
				PlayerPickedUpItem,
				PlayerStartedMoving,
				PlayerStoppedMoving,
				ProjectileImpact
			};
		}
	}
}