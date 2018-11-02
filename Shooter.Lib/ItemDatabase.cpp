#include "ItemDatabase.h"

#include <fstream>

#include "json.hpp"

using nlohmann::json;

using namespace Shooter::WorldDatabase::Items;

const std::string TEXTURES_PATH = "Resources/textures/";

static WeaponDescriptor parseWeaponDescriptor(json::value_type& jsonValue);

ItemDatabase::ItemDatabase(std::string fileName) {
	std::ifstream fileStream(fileName);

	json json;
	fileStream >> json;

	ItemDescriptor itemDescriptor;
	for (json::iterator it = json.begin(); it != json.end(); ++it) {
		json::value_type item = *it;

		ItemType itemType = item.at("itemType").get<ItemType>();

		itemDescriptor.id = item.at("id").get<std::string>();
		itemDescriptor.name = item.at("name").get<std::string>();
		itemDescriptor.itemType = itemType;
		itemDescriptor.width = item.at("width").get<int>();
		itemDescriptor.height = item.at("height").get<int>();
		itemDescriptor.weight = item.at("weight").get<int>();
		itemDescriptor.texture = TEXTURES_PATH + item.at("texture").get<std::string>();

		switch (itemType)
		{
		case ItemType::Weapon:
			WeaponDescriptor weaponDescriptor = parseWeaponDescriptor(item);
			itemDescriptor.weapon = weaponDescriptor;
			break;

		default:
			std::stringstream message;
			message << "Unknown item type '" << itemType << "'.";
			throw std::invalid_argument(message.str());
		}

		_items[itemDescriptor.id] = itemDescriptor;
	}
}

ItemDescriptor& ItemDatabase::getItem(std::string& id) {
	return _items[id];
}

static WeaponDescriptor parseWeaponDescriptor(json::value_type& jsonValue) {
	WeaponDescriptor weaponDescriptor;

	WeaponType weaponType = jsonValue.at("itemType").get<WeaponType>();

	weaponDescriptor.weaponType = weaponType;

	switch (weaponType)
	{
	case WeaponType::Firearm:
		FirearmDescriptor firearmDescriptor;

		firearmDescriptor.capacity = jsonValue.at("capacity").get<int>();
		firearmDescriptor.damage = jsonValue.at("damage").get<int>();
		firearmDescriptor.muzzleVelocity = jsonValue.at("muzzleVelocity").get<double>();
		firearmDescriptor.roundsPerMinute = jsonValue.at("roundsPerMinute").get<int>();

		weaponDescriptor.firearm = firearmDescriptor;
		break;

	default:
		std::stringstream message;
		message << "Unkown weapon type '" << weaponType << "'.";
		throw new std::invalid_argument(message.str());
	}

	return weaponDescriptor;
}