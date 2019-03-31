#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "Crosshair.h"
#include "GameEvent.h"
#include "IGameSet.h"
#include "IGameSettings.h"
#include "IGameState.h"
#include "IInputEventHandler.h"
#include "IInputManager.h"
#include "INonPlayingCharacter.h"
#include "IPlayer.h"
#include "Projectile.h"

using namespace Shooter::Input;
using namespace Shooter::Math;

namespace Shooter {
	namespace World {
		class GameState : public IGameState
		{
		public:
			GameState(
				IGameSet& gameSet,
				IGameSettings& gameSettings,
				IInputEventHandler& inputEventHandler,
				IInputManager& inputManager,
				Crosshair& crosshair,
				std::vector<std::shared_ptr<INonPlayingCharacter>>& nonPlayingCharacters,
				IPlayer& player,
				Camera& camera);

			Camera& getCamera();
			Crosshair& getCrosshair();
			IGameSet& getGameSet() const;
			std::vector<std::shared_ptr<INonPlayingCharacter>>& getNonPlayingCharacters();
			IPlayer& getPlayer() const;
			PlayerMovementState& getPlayerMovementState();
			std::vector<std::shared_ptr<Projectile>>& getProjectiles();
			std::shared_ptr<IItem> getSelectedItem();
			bool isStopped();
			void selectItemAtPosition(Vector2& position);
			void setSelectedItem(std::shared_ptr<IItem> selectedItem);
			void stop();
			std::vector<GameEvent> update(sf::Time elapsedTime, std::vector<sf::Event>& events);

		private:
			std::shared_ptr<IItem> _selectedItem;
			bool _isStopped;
			Camera& _camera;
			Crosshair _crosshair;
			IGameSet& _gameSet;
			IGameSettings& _gameSettings;
			IInputEventHandler& _inputEventHandler;
			IInputManager& _inputManager;
			std::vector<std::shared_ptr<INonPlayingCharacter>> _nonPlayingCharacters;
			IPlayer& _player;
			PlayerMovementState _playerMovementState;
			std::vector<std::shared_ptr<Projectile>> _projectiles;
		};
	}
}