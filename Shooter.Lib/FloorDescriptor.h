#pragma once

#include <string>

#include "json.hpp"

using nlohmann::json;

namespace Shooter {
	namespace LevelDescriptors {
		struct FloorDescriptor {
		public:
			std::string texture;
			double x;
			double y;
			double orientation;
			int width;
			int length;
		};

		void to_json(json& j, const FloorDescriptor& p);

		void from_json(const json& j, FloorDescriptor& p);
	}
}