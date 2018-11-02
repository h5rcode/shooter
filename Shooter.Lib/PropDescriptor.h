#pragma once

#include <string>

namespace Shooter {
	namespace WorldDatabase {
		namespace Props {
			struct PropDescriptor {
				std::string id;
				std::string name;
				int width;
				int height;
				std::string texture;
			};
		}
	}
}