#include "WallDescriptor.h"

#include "json.hpp"

using nlohmann::json;

namespace Shooter {
	namespace LevelDescriptors {
		void to_json(json& j, const WallDescriptor& p) {
			j = json{
				{"texture", p.texture},
				{"x", p.x},
				{"y", p.y},
				{"orientation", p.orientation},
				{"width", p.width},
				{"length", p.length}
			};
		}

		void from_json(const json& j, WallDescriptor& p) {
			j.at("texture").get_to(p.texture);
			j.at("x").get_to(p.x);
			j.at("y").get_to(p.y);
			j.at("orientation").get_to(p.orientation);
			j.at("width").get_to(p.width);
			j.at("length").get_to(p.length);
		}
	}
}