#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "IGameSet.h"

#include "Camera.h"
#include "Crosshair.h"
#include "GameEvent.h"
#include "INonPlayingCharacter.h"
#include "IPlayer.h"
#include "Projectile.h"

using namespace Shooter::Items::Weapons;
using namespace Shooter::Npcs;
using namespace Shooter::World::Events;

namespace Shooter {
	namespace World {
		struct PlayerMovementState {
			PlayerMovementState() :
				up(false),
				down(false),
				left(false),
				right(false) {
			}

			bool up;
			bool down;
			bool left;
			bool right;
		};

		class IGameState {
		public:
			virtual Camera& getCamera() = 0;
			virtual Crosshair& getCrosshair() = 0;
			virtual IGameSet& getGameSet() const = 0;
			virtual std::vector<std::shared_ptr<INonPlayingCharacter>>& getNonPlayingCharacters() = 0;
			virtual IPlayer& getPlayer() const = 0;
			virtual PlayerMovementState& getPlayerMovementState() = 0;
			virtual std::vector<std::shared_ptr<Projectile>>& getProjectiles() = 0;
			virtual std::shared_ptr<IItem> getSelectedItem() = 0;
			virtual void setSelectedItem(std::shared_ptr<IItem> selectedItem) = 0;
			virtual void stop() = 0;
			virtual std::vector<GameEvent> update(sf::Time elapsedTime, std::vector<sf::Event>& events) = 0;
		};
	}
}