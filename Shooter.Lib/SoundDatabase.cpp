#include "SoundDatabase.h"

#include <fstream>

#include "json.hpp"

using nlohmann::json;

using namespace Shooter::WorldDatabase::Sounds;

SoundDatabase::SoundDatabase(std::string filename)
{
	std::ifstream fileStream(filename);

	json json;
	fileStream >> json;

	SoundDescriptor soundDescriptor;
	for (json::iterator it = json.begin(); it != json.end(); ++it)
	{
		json::value_type item = *it;

		soundDescriptor.name = item.at("name").get<std::string>();
		soundDescriptor.filename = item.at("filename").get<std::string>();

		_sounds[soundDescriptor.name] = soundDescriptor;
	}
}

std::string& SoundDatabase::getBulletImpactFilename()
{
	return getSoundFilename("bulletImpact");
}

std::string& SoundDatabase::getFootstepFilename()
{
	return getSoundFilename("footStep");
}

std::string& SoundDatabase::getGruntFilename()
{
	return getSoundFilename("grunt");
}

std::string& SoundDatabase::getPickupItemFilename()
{
	return getSoundFilename("pickupItem");
}

std::string& SoundDatabase::getSoundFilename(std::string name)
{
	SoundDescriptor& soundDescriptor = _sounds[name];
	return soundDescriptor.filename;
}