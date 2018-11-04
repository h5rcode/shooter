#pragma once

#include <string>

#include "json.hpp"

using nlohmann::json;

namespace Shooter {
	namespace LevelDescriptors {
		struct LevelPropDescriptor {
			std::string propId;
			double x;
			double y;
			double orientation;
		};

		void to_json(json& j, const LevelPropDescriptor& p);

		void from_json(const json& j, LevelPropDescriptor& p);
	}
}