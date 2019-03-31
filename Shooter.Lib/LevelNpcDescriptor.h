#pragma once

#include <string>

#include "json.hpp"

using nlohmann::json;

namespace Shooter {
	namespace LevelDescriptors {
		struct LevelNpcDescriptor {
			std::string npcId;
			double x;
			double y;
			double orientation;
		};

		void to_json(json& j, const LevelNpcDescriptor& p);

		void from_json(const json& j, LevelNpcDescriptor& p);
	}
}