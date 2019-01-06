#include "ItemDatabase.h"

#include <fstream>
#include <sstream>

#include "json.hpp"

#include "FirearmDescriptor.h"

using nlohmann::json;

using namespace Shooter::WorldDatabase::Items;

static std::shared_ptr<WeaponDescriptor> parseWeaponDescriptor(json::value_type& jsonValue);

ItemDatabase::ItemDatabase(std::string fileName) {
	std::ifstream fileStream(fileName);

	json json;
	fileStream >> json;

	for (json::iterator it = json.begin(); it != json.end(); ++it) {
		json::value_type jsonValue = *it;

		std::shared_ptr<ItemDescriptor> itemDescriptor = std::make_shared<ItemDescriptor>();
		itemDescriptor->id = jsonValue.at("id").get<std::string>();
		itemDescriptor->name = jsonValue.at("name").get<std::string>();
		itemDescriptor->itemType = ItemType::Weapon;
		itemDescriptor->width = jsonValue.at("width").get<int>();
		itemDescriptor->height = jsonValue.at("height").get<int>();
		itemDescriptor->weight = jsonValue.at("weight").get<int>();
		itemDescriptor->texture = jsonValue.at("texture").get<std::string>();

		ItemType itemType = jsonValue.at("itemType").get<ItemType>();

		switch (itemType)
		{
		case ItemType::Weapon:
			itemDescriptor->weapon = parseWeaponDescriptor(jsonValue);
			break;

		default:
			std::stringstream message;
			message << "Unknown item type '" << itemType << "'.";
			throw std::invalid_argument(message.str());
		}

		_items[itemDescriptor->id] = itemDescriptor;
	}
}

std::vector<std::string> ItemDatabase::getAllSoundFilenames() {
	std::vector<std::string> soundFilenames;

	for (auto& it : _items)
	{
		ItemDescriptor& itemDescriptor = *it.second;

		if (itemDescriptor.itemType == ItemType::Weapon) {
			std::shared_ptr< WeaponDescriptor> weaponDescriptor = itemDescriptor.weapon;

			if (weaponDescriptor->weaponType == WeaponType::Firearm) {
				FirearmDescriptor& firearmDescriptor = *weaponDescriptor->Firearm;

				soundFilenames.push_back(firearmDescriptor.gunshotSound);
			}
		}
	}

	return soundFilenames;
}

ItemDescriptor& ItemDatabase::getItem(std::string& id) {
	return *_items[id];
}

static std::shared_ptr<WeaponDescriptor> parseWeaponDescriptor(json::value_type& jsonValue) {
	WeaponType weaponType = jsonValue.at("itemType").get<WeaponType>();

	std::shared_ptr<WeaponDescriptor> weaponDescriptor = std::make_shared<WeaponDescriptor>();
	weaponDescriptor->weaponType = weaponType;
	switch (weaponType)
	{
	case WeaponType::Firearm:
	{
		std::shared_ptr<FirearmDescriptor> firearmDescriptor = std::make_shared<FirearmDescriptor>();
		firearmDescriptor->capacity = jsonValue.at("capacity").get<int>();
		firearmDescriptor->damage = jsonValue.at("damage").get<int>();
		firearmDescriptor->muzzleVelocity = jsonValue.at("muzzleVelocity").get<double>();
		firearmDescriptor->roundsPerMinute = jsonValue.at("roundsPerMinute").get<int>();
		firearmDescriptor->gunshotSound = jsonValue.at("gunshotSound").get<std::string>();

		weaponDescriptor->Firearm = firearmDescriptor;
	}
	break;

	default:
		std::stringstream message;
		message << "Unkown weapon type '" << weaponType << "'.";
		throw new std::invalid_argument(message.str());
	}

	return weaponDescriptor;
}