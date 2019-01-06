#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "Crosshair.h"
#include "IGameSet.h"
#include "IGameSettings.h"
#include "IGameState.h"
#include "IInputEventHandler.h"
#include "IInputManager.h"
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
				IPlayer& player,
				Camera& camera);

			Camera& getCamera();
			Crosshair& getCrosshair();
			std::vector<GameEvent>& getGameEvents();
			IGameSet& getGameSet() const;
			IPlayer& getPlayer() const;
			Vector2& getPlayerMovementState();
			std::vector<std::shared_ptr<Projectile>>& getProjectiles();
			std::shared_ptr<IItem> getSelectedItem();
			bool isStopped();
			void processInput();
			void selectItemAtPosition(Vector2& position);
			void setSelectedItem(std::shared_ptr<IItem> selectedItem);
			void stop();
			void update(sf::Time elapsedTime);

		private:
			std::vector<GameEvent> _gameEvents;
			std::shared_ptr<IItem> _selectedItem;
			bool _isStopped;
			Camera& _camera;
			Crosshair _crosshair;
			IGameSet& _gameSet;
			IGameSettings& _gameSettings;
			IInputEventHandler& _inputEventHandler;
			IInputManager& _inputManager;
			IPlayer& _player;
			Vector2 _playerMovementState;
			std::vector<std::shared_ptr<Projectile>> _projectiles;
		};
	}
}