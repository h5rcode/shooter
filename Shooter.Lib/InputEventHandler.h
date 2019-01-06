#pragma once

#include "AttackCommand.h"
#include "IInputEventHandler.h"
#include "IInputManager.h"
#include "UpdatePlayerMovementStateCommand.h"
#include "UseCommand.h"

using namespace Shooter::World::Commands;
using namespace Shooter::Input;

namespace Shooter {
	namespace World {
		class InputEventHandler : public IInputEventHandler {
		public:
			InputEventHandler(IInputManager& inputManager);

		public:
			std::vector<GameEvent> handle(IGameState& gameState, sf::Event& event);

		private:
			IInputManager& _inputManager;

			AttackCommand _attackCommand;
			UseCommand _useCommand;
			UpdatePlayerMovementStateCommand _updatePlayerMovementStateCommand;
		};
	}
}