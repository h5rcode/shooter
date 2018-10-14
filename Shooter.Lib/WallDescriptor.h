#pragma once

#include <string>

namespace Shooter {
	namespace LevelDescriptors {
		struct WallDescriptor {
		public:
			std::string texture;
			double x;
			double y;
			double orientation;
			int width;
			int length;
		};
	}
}