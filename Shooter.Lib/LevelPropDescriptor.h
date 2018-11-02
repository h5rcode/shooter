#pragma once

#include <string>

namespace Shooter {
	namespace LevelDescriptors {
		struct LevelPropDescriptor {
			std::string id;
			double x;
			double y;
			double orientation;
		};
	}
}