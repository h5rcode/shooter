#pragma once

#include <string>
#include <vector>

#include "NonPlayingCharacterDescriptor.h"

namespace Shooter {
	namespace WorldDatabase {
		namespace Npcs {
			class INonPlayingCharacterDatabase {
			public:
				virtual NonPlayingCharacterDescriptor& getNpc(std::string& id) = 0;
			};
		}
	}
}