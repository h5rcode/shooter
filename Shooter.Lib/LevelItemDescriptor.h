#pragma once

#include <string>

#include "json.hpp"

using nlohmann::json;

namespace Shooter {
	namespace LevelDescriptors {
		struct LevelItemDescriptor {
			std::string itemId;
			double x;
			double y;
			double orientation;
		};

		void to_json(json& j, const LevelItemDescriptor& p);

		void from_json(const json& j, LevelItemDescriptor& p);
	}
}