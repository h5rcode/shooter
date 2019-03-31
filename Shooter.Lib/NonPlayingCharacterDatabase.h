#pragma once

#include <map>
#include <string>

#include "INonPlayingCharacterDatabase.h"
#include "NonPlayingCharacterDescriptor.h"

namespace Shooter {
	namespace WorldDatabase {
		namespace Npcs {
			class NonPlayingCharacterDatabase : public INonPlayingCharacterDatabase {
			public:
				NonPlayingCharacterDatabase(std::string fileName);

			public:
				NonPlayingCharacterDescriptor& getNpc(std::string& id);

			private:
				std::map<std::string, std::shared_ptr<NonPlayingCharacterDescriptor>> _npcs;
			};
		}
	}
}