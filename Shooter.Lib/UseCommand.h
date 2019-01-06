#pragma once

#include "IGameState.h"

namespace Shooter {
	namespace World {
		namespace Commands {
			class UseCommand {
			public:
				std::vector<GameEvent> execute(IGameState& gameState);
			};
		}
	}
}