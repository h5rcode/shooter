#pragma once

#include <string>

namespace Shooter {
	namespace WorldDatabase {
		namespace Npcs {
			struct NonPlayingCharacterDescriptor {
				std::string id;
				std::string name;
				std::string texture;
				int width;
				int height;
			};
		}
	}
}