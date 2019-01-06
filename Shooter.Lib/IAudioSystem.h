#pragma once

#include <vector>

#include "GameEvent.h"

using namespace Shooter::World::Events;

namespace Shooter {
	namespace Audio {
		class IAudioSystem {
		public:
			virtual void update(std::vector<GameEvent>& gameEvents) = 0;
		};
	}
}
