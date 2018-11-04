#pragma once

#include <string>

#include "json.hpp"

using nlohmann::json;

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

		void to_json(json& j, const WallDescriptor& p);

		void from_json(const json& j, WallDescriptor& p);
	}
}