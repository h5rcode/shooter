#include "UpdatePlayerMovementStateCommand.h"

using namespace Shooter::World::Commands;

void UpdatePlayerMovementStateCommand::execute(IGameState& gameState, MovementDirection direction, MovementType movementType)
{
	Vector2& playerMovementState = gameState.getPlayerMovementState();

	bool isStopping = movementType == MovementType::STOP;

	switch (direction)
	{
	case Shooter::World::Commands::UP:
		playerMovementState.y = isStopping ? 0 : -1;
		break;
	case Shooter::World::Commands::DOWN:
		playerMovementState.y = isStopping ? 0 : 1;
		break;
	case Shooter::World::Commands::LEFT:
		playerMovementState.x = isStopping ? 0 : -1;
		break;
	case Shooter::World::Commands::RIGHT:
		playerMovementState.x = isStopping ? 0 : 1;
		break;
	}
}