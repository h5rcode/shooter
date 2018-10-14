#include "Firearm.h"
#include "ItemFactory.h"
#include "StaticRenderable.h"

using namespace Shooter::ItemDatabase;
using namespace Shooter::Items;
using namespace Shooter::Math;

ItemFactory::ItemFactory(IItemDatabase& itemDatabase, IResourceManager& resourceManager)
	:
	_itemDatabase(itemDatabase),
	_resourceManager(resourceManager) {
}

std::shared_ptr<IItem> ItemFactory::buildItem(std::string itemId, Vector2& position, double orientation)
{
	ItemDescriptor& itemDescriptor = _itemDatabase.getItem(itemId);

	int width = itemDescriptor.width;
	int height = itemDescriptor.height;
	std::string& textureFilename = itemDescriptor.texture;

	sf::Texture* texture = _resourceManager.getTexture(textureFilename);

	std::shared_ptr<StaticRenderable> itemRenderable = std::make_shared<StaticRenderable>(position, width, height, orientation, *texture);

	switch (itemDescriptor.itemType)
	{
	case ItemType::Weapon:
		WeaponDescriptor weaponDescriptor = itemDescriptor.weapon;

		switch (weaponDescriptor.weaponType)
		{
		case WeaponType::Firearm:
			FirearmDescriptor firearmDescriptor = weaponDescriptor.firearm;
			return std::make_shared<Shooter::Items::Weapons::Firearm>(
				itemDescriptor.name,
				firearmDescriptor.capacity,
				firearmDescriptor.damage,
				firearmDescriptor.muzzleVelocity,
				firearmDescriptor.roundsPerMinute,
				itemDescriptor.weight,
				position,
				width,
				height,
				orientation,
				_resourceManager,
				itemRenderable);

		default:
			throw std::invalid_argument("Unkown weapon type: '" + weaponDescriptor.weaponType);
		}

		break;
	default:
		break;
	}

	return NULL;
}
