#pragma once

#include "IGameSettings.h"

namespace Shooter {
	namespace Input {
		class GameSettings : public IGameSettings {
		public:
			GameSettings();

		public:
			double getAccelerationNorm() const;
		};
	}
}