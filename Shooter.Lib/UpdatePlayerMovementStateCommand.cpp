#include "UpdatePlayerMovementStateCommand.h"

using namespace Shooter::World::Commands;

void UpdatePlayerMovementStateCommand::execute(IGameState& gameState, MovementDirection direction, MovementType movementType)
{
	PlayerMovementState& playerMovementState = gameState.getPlayerMovementState();

	bool isStarting = movementType == MovementType::START;

	switch (direction)
	{
	case Shooter::World::Commands::UP:
		playerMovementState.up = isStarting;
		break;
	case Shooter::World::Commands::DOWN:
		playerMovementState.down = isStarting;
		break;
	case Shooter::World::Commands::LEFT:
		playerMovementState.left = isStarting;
		break;
	case Shooter::World::Commands::RIGHT:
		playerMovementState.right = isStarting;
		break;
	}
}