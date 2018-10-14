#pragma once

#include <memory>
#include <vector>

#include "IGameSet.h"

#include "Camera.h"
#include "Crosshair.h"
#include "IPlayer.h"
#include "Projectile.h"

using namespace Shooter::Items::Weapons;

namespace Shooter {
	namespace World {
		class IGameState {
		public:
			virtual Camera& getCamera() = 0;
			virtual Crosshair& getCrosshair() = 0;
			virtual IGameSet& getGameSet() const = 0;
			virtual IPlayer& getPlayer() const = 0;
			virtual std::vector<std::shared_ptr<Projectile>>& getProjectiles() = 0;
		};
	}
}