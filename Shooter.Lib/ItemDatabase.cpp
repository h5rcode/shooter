#include "ItemDatabase.h"

#include <fstream>
#include <sstream>

#include "json.hpp"

#include "FirearmDescriptor.h"

using nlohmann::json;

using namespace Shooter::WorldDatabase::Items;

static WeaponDescriptor* parseWeaponDescriptor(json::value_type& jsonValue);

ItemDatabase::ItemDatabase(std::string fileName) {
	std::ifstream fileStream(fileName);

	json json;
	fileStream >> json;

	ItemDescriptor* itemDescriptor;
	for (json::iterator it = json.begin(); it != json.end(); ++it) {
		json::value_type item = *it;

		ItemType itemType = item.at("itemType").get<ItemType>();

		switch (itemType)
		{
		case ItemType::Weapon:
			itemDescriptor = parseWeaponDescriptor(item);
			break;

		default:
			std::stringstream message;
			message << "Unknown item type '" << itemType << "'.";
			throw std::invalid_argument(message.str());
		}

		_items[itemDescriptor->id] = itemDescriptor;
	}
}

ItemDatabase::~ItemDatabase()
{
	for (auto& it : _items)
	{
		delete it.second;
	}
}

ItemDescriptor* ItemDatabase::getItem(std::string& id) {
	return _items[id];
}

static WeaponDescriptor* parseWeaponDescriptor(json::value_type& jsonValue) {
	WeaponType weaponType = jsonValue.at("itemType").get<WeaponType>();
	switch (weaponType)
	{
	case WeaponType::Firearm:
	{
		FirearmDescriptor* firearmDescriptor = new FirearmDescriptor();
		firearmDescriptor->id = jsonValue.at("id").get<std::string>();
		firearmDescriptor->name = jsonValue.at("name").get<std::string>();
		firearmDescriptor->itemType = ItemType::Weapon;
		firearmDescriptor->weaponType = weaponType;
		firearmDescriptor->width = jsonValue.at("width").get<int>();
		firearmDescriptor->height = jsonValue.at("height").get<int>();
		firearmDescriptor->weight = jsonValue.at("weight").get<int>();
		firearmDescriptor->texture = jsonValue.at("texture").get<std::string>();
		firearmDescriptor->capacity = jsonValue.at("capacity").get<int>();
		firearmDescriptor->damage = jsonValue.at("damage").get<int>();
		firearmDescriptor->muzzleVelocity = jsonValue.at("muzzleVelocity").get<double>();
		firearmDescriptor->roundsPerMinute = jsonValue.at("roundsPerMinute").get<int>();
		firearmDescriptor->gunshotSound = jsonValue.at("gunshotSound").get<std::string>();

		return firearmDescriptor;
	}
	break;

	default:
		std::stringstream message;
		message << "Unkown weapon type '" << weaponType << "'.";
		throw new std::invalid_argument(message.str());
	}
}