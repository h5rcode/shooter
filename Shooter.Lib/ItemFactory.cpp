#include "ItemFactory.h"
#include "Firearm.h"

std::shared_ptr<IItem> ItemFactory::buildItem(std::string itemId, Vector2& position, double orientation, std::string& texture)
{
	if (itemId == "SIGSAUER") {
		return std::make_shared<Firearm>(20, 30, 20, 60, 1, position, 32, 32, orientation, texture);
	}

	// TODO.
	return NULL;
}
