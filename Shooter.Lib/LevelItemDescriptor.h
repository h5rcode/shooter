#pragma once

#include <string>

namespace Shooter {
	namespace LevelDescriptors {
		struct LevelItemDescriptor {
		public:
			std::string itemId;
			double x;
			double y;
			double orientation;
			std::string texture;
		};
	}
}