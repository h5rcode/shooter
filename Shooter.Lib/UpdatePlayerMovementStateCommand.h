#pragma once

#include "IGameState.h"

namespace Shooter {
	namespace World {
		namespace Commands {
			enum MovementDirection {
				UP,
				DOWN,
				LEFT,
				RIGHT
			};

			enum MovementType {
				START,
				STOP
			};

			class UpdatePlayerMovementStateCommand {
			public:
				void execute(IGameState& gameState, MovementDirection direction, MovementType movementType);
			};
		}
	}
}