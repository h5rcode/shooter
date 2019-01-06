#pragma once

#include <memory>
#include <vector>

#include "IGameSet.h"

#include "Camera.h"
#include "Crosshair.h"
#include "GameEvent.h"
#include "IPlayer.h"
#include "Projectile.h"

using namespace Shooter::Items::Weapons;
using namespace Shooter::World::Events;

namespace Shooter {
	namespace World {
		class IGameState {
		public:
			virtual Camera& getCamera() = 0;
			virtual Crosshair& getCrosshair() = 0;
			virtual std::vector<GameEvent>& getGameEvents() = 0;
			virtual IGameSet& getGameSet() const = 0;
			virtual IPlayer& getPlayer() const = 0;
			virtual Vector2& getPlayerMovementState() = 0;
			virtual std::vector<std::shared_ptr<Projectile>>& getProjectiles() = 0;
			virtual std::shared_ptr<IItem> getSelectedItem() = 0;
			virtual void setSelectedItem(std::shared_ptr<IItem> selectedItem) = 0;
			virtual void stop() = 0;
		};
	}
}