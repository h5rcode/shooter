#include "UpdatePlayerMovementStateCommand.h"

using namespace Shooter::World::Commands;

void UpdatePlayerMovementStateCommand::execute(IGameState& gameState, MovementDirection direction, MovementType movementType)
{
	Vector2& playerMovementState = gameState.getPlayerMovementState();

	switch (direction)
	{
	case Shooter::World::Commands::UP:
		playerMovementState.y = movementType == MovementType::STOPPED ? 0 : -1;
		break;
	case Shooter::World::Commands::DOWN:
		playerMovementState.y = movementType == MovementType::STOPPED ? 0 : 1;
		break;
	case Shooter::World::Commands::LEFT:
		playerMovementState.x = movementType == MovementType::STOPPED ? 0 : -1;
		break;
	case Shooter::World::Commands::RIGHT:
		playerMovementState.x = movementType == MovementType::STOPPED ? 0 : 1;
		break;
	}
}