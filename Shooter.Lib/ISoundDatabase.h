#pragma once

#include "SoundDescriptor.h"

namespace Shooter {
	namespace WorldDatabase {
		namespace Sounds {
			class ISoundDatabase {
			public:
				virtual std::string& getBulletImpactFilename() = 0;
				virtual std::string& getFootstepFilename() = 0;
				virtual std::string& getGruntFilename() = 0;
				virtual std::string& getPickupItemFilename() = 0;
			};
		}
	}
}