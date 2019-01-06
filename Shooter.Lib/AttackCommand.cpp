#include "AttackCommand.h"

using namespace Shooter::World::Commands;

std::vector<GameEvent> AttackCommand::execute(IGameState& gameState)
{
	std::vector<GameEvent> gameEvents;
	IPlayer& player = gameState.getPlayer();

	if (player.canAttack())
	{
		Crosshair& _crosshair = gameState.getCrosshair();

		Vector2& crosshairPosition = _crosshair.getPosition();
		std::vector<std::shared_ptr<Projectile>> newProjectiles = player.attackToward(crosshairPosition);

		std::vector<std::shared_ptr<Projectile>>& projectiles = gameState.getProjectiles();
		for each (std::shared_ptr<Projectile> projectile in newProjectiles)
		{
			projectiles.push_back(projectile);
		}

		gameEvents.push_back(GameEvent{ GameEventType::PlayerAttacked });
	}

	return gameEvents;
}