#pragma once

namespace Shooter {
	namespace World {
		namespace Events {
			enum GameEventType {
				PlayerAttacked,
				PlayerHurt,
				PlayerImmobilized,
				PlayerPickedUpItem
			};
		}
	}
}