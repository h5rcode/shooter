#pragma once

#include "AttackCommand.h"
#include "IInputEventHandler.h"
#include "IInputManager.h"
#include "UpdatePlayerMovementStateCommand.h"
#include "UseCommand.h"

using namespace Shooter::World::Commands;

namespace Shooter {
	namespace World {
		class InputEventHandler : public IInputEventHandler {
		public:
			std::vector<GameEvent> handle(IGameState& gameState, sf::Event& event);

		private:
			AttackCommand _attackCommand;
			UseCommand _useCommand;
			UpdatePlayerMovementStateCommand _updatePlayerMovementStateCommand;
		};
	}
}