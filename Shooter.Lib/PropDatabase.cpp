#include "PropDatabase.h"

#include <fstream>

#include "json.hpp"

using nlohmann::json;

using namespace Shooter::WorldDatabase::Props;

const std::string TEXTURES_PATH = "Resources/textures/";

PropDatabase::PropDatabase(std::string filename) {
	std::ifstream fileStream(filename);

	json json;
	fileStream >> json;

	PropDescriptor itemDescriptor;
	for (json::iterator it = json.begin(); it != json.end(); ++it) {
		json::value_type item = *it;

		itemDescriptor.id = item.at("id").get<std::string>();
		itemDescriptor.name = item.at("name").get<std::string>();
		itemDescriptor.width = item.at("width").get<int>();
		itemDescriptor.height = item.at("height").get<int>();
		itemDescriptor.texture = TEXTURES_PATH + item.at("texture").get<std::string>();

		_props[itemDescriptor.id] = itemDescriptor;
	}
}

PropDescriptor& PropDatabase::getProp(std::string& id) {
	return _props[id];
}