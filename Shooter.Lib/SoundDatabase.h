#pragma once

#include <map>

#include "ISoundDatabase.h"

namespace Shooter {
	namespace WorldDatabase {
		namespace Sounds {
			class SoundDatabase : public ISoundDatabase {
			public:
				SoundDatabase(std::string filename);
			public:
				std::string& getBulletImpactFilename();
				std::string& getFootstepFilename();
				std::string& getGruntFilename();
				std::string& getPickupItemFilename();
			private:
				std::string& getSoundFilename(std::string name);
			private:
				std::map<std::string, SoundDescriptor> _sounds;
			};
		}
	}
}