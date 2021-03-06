#include "Firearm.h"
#include "FirearmDescriptor.h"
#include "ItemFactory.h"
#include "WeaponDescriptor.h"

using namespace Shooter::WorldDatabase::Items;
using namespace Shooter::Items;
using namespace Shooter::Math;

ItemFactory::ItemFactory(IItemDatabase& itemDatabase) :
	_itemDatabase(itemDatabase) {
}

std::shared_ptr<IItem> ItemFactory::buildItem(std::string itemId, Vector2& position, double orientation)
{
	ItemDescriptor& itemDescriptor = _itemDatabase.getItem(itemId);

	int width = itemDescriptor.width;
	int height = itemDescriptor.height;

	switch (itemDescriptor.itemType)
	{
	case ItemType::Weapon:
	{
		std::shared_ptr<WeaponDescriptor> weaponDescriptor = itemDescriptor.weapon;

		switch (weaponDescriptor->weaponType)
		{
		case WeaponType::Firearm:
		{
			std::shared_ptr<FirearmDescriptor> firearmDescriptor = weaponDescriptor->Firearm;
			return std::make_shared<Shooter::Items::Weapons::Firearm>(
				itemDescriptor.id,
				itemDescriptor.name,
				firearmDescriptor->capacity,
				firearmDescriptor->damage,
				firearmDescriptor->muzzleVelocity,
				firearmDescriptor->roundsPerMinute,
				itemDescriptor.weight,
				position,
				width,
				height,
				orientation);
		}
		default:
			throw std::invalid_argument("Unkown weapon type: '" + weaponDescriptor->weaponType);
		}

		break;
	}
	default:
		break;
	}

	return NULL;
}
