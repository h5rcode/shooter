#pragma once

namespace Shooter {
	namespace Input {
		class IGameSettings {
		public:
			virtual double getAccelerationNorm() const = 0;
		};
	}
}