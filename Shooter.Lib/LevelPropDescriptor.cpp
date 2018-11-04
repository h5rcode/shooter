#include "LevelPropDescriptor.h"

#include "json.hpp"

using nlohmann::json;

namespace Shooter {
	namespace LevelDescriptors {
		void to_json(json& j, const LevelPropDescriptor& p) {
			j = json{
				{"propId", p.propId},
				{"x", p.x},
				{"y", p.y},
				{"orientation", p.orientation}
			};
		}

		void from_json(const json& j, LevelPropDescriptor& p) {
			j.at("propId").get_to(p.propId);
			j.at("x").get_to(p.x);
			j.at("y").get_to(p.y);
			j.at("orientation").get_to(p.orientation);
		}
	}
}