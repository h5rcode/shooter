#include "UseCommand.h"

using namespace Shooter::World::Commands;

std::vector<GameEvent> UseCommand::execute(IGameState& gameState)
{
	std::vector<GameEvent> gameEvents;

	std::shared_ptr<IItem> selectedItem = gameState.getSelectedItem();
	IPlayer& _player = gameState.getPlayer();
	IGameSet& _gameSet = gameState.getGameSet();

	if (selectedItem != NULL) {
		bool itemWasPickedUp = _player.pickUpItem(selectedItem);

		if (itemWasPickedUp) {

			GameEvent gameEvent;
			gameEvent.Type = GameEventType::PlayerPickedUpItem;
			gameEvent.PlayerPickedUpItem = PlayerPickedUpItemEvent{ selectedItem };
			gameEvents.push_back(gameEvent);
			_gameSet.removeItem(selectedItem);

			std::shared_ptr<IWeapon> weapon = std::dynamic_pointer_cast<IWeapon>(selectedItem);
			if (weapon != NULL && _player.getEquipedWeapon() == NULL) {
				_player.equipWeapon(weapon);
			}

			gameState.setSelectedItem(NULL);
		}
	}

	return gameEvents;
}