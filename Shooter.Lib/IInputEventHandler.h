#pragma once

#include <vector>

#include "IGameState.h"

namespace Shooter {
	namespace World {
		class IInputEventHandler {
		public:
			virtual std::vector<GameEvent> handle(IGameState& gameState, sf::Event& event) = 0;
		};
	}
}