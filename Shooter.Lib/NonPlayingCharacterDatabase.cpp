#include "ItemDatabase.h"

#include <fstream>
#include <sstream>

#include "NonPlayingCharacterDatabase.h"

#include "json.hpp"

using nlohmann::json;

using namespace Shooter::WorldDatabase::Npcs;

NonPlayingCharacterDatabase::NonPlayingCharacterDatabase(std::string fileName) {
	std::ifstream fileStream(fileName);

	json json;
	fileStream >> json;

	for (json::iterator it = json.begin(); it != json.end(); ++it) {
		json::value_type jsonValue = *it;

		std::shared_ptr<NonPlayingCharacterDescriptor> npcDescriptor = std::make_shared<NonPlayingCharacterDescriptor>();
		npcDescriptor->id = jsonValue.at("id").get<std::string>();
		npcDescriptor->name = jsonValue.at("name").get<std::string>();
		npcDescriptor->width = jsonValue.at("width").get<int>();
		npcDescriptor->height = jsonValue.at("height").get<int>();
		npcDescriptor->texture = jsonValue.at("texture").get<std::string>();

		_npcs[npcDescriptor->id] = npcDescriptor;
	}
}

NonPlayingCharacterDescriptor& NonPlayingCharacterDatabase::getNpc(std::string& id) {
	return *_npcs[id];
}
