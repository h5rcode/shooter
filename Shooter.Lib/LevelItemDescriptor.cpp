#include "LevelItemDescriptor.h"

#include "json.hpp"

using nlohmann::json;

namespace Shooter {
	namespace LevelDescriptors {
		void to_json(json& j, const LevelItemDescriptor& p) {
			j = json{
				{"itemId", p.itemId},
				{"x", p.x},
				{"y", p.y},
				{"orientation", p.orientation}
			};
		}

		void from_json(const json& j, LevelItemDescriptor& p) {
			j.at("itemId").get_to(p.itemId);
			j.at("x").get_to(p.x);
			j.at("y").get_to(p.y);
			j.at("orientation").get_to(p.orientation);
		}
	}
}