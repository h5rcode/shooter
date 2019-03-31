#include "LevelNpcDescriptor.h"

#include "json.hpp"

using nlohmann::json;

namespace Shooter {
	namespace LevelDescriptors {
		void to_json(json& j, const LevelNpcDescriptor& p) {
			j = json{
				{"npcId", p.npcId},
				{"x", p.x},
				{"y", p.y},
				{"orientation", p.orientation}
			};
		}

		void from_json(const json& j, LevelNpcDescriptor& p) {
			j.at("npcId").get_to(p.npcId);
			j.at("x").get_to(p.x);
			j.at("y").get_to(p.y);
			j.at("orientation").get_to(p.orientation);
		}
	}
}