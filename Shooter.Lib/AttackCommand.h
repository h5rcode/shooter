#pragma once

#include "GameEvent.h"
#include "IGameState.h"

using namespace Shooter::World::Events;

namespace Shooter {
	namespace World {
		namespace Commands {
			class AttackCommand {
			public:
				std::vector<GameEvent> execute(IGameState& gameState);
			};
		}
	}
}