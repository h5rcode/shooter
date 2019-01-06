#pragma once

#include <vector>

#include "GameEvent.h"
#include "IGameState.h"

using namespace Shooter::World::Events;

namespace Shooter {
	namespace World {
		class IInputEventHandler {
		public:
			virtual std::vector<GameEvent> handle(IGameState& gameState, sf::Event& event) = 0;
		};
	}
}