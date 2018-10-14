#pragma once

#include <string>

namespace Shooter {
	namespace LevelDescriptors {
		struct PropDescriptor {
			std::string texture;
			double x;
			double y;
			double orientation;
			int width;
			int height;
		};
	}
}