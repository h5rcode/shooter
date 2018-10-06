#include "Firearm.h"
#include "ItemFactory.h"
#include "StaticRenderable.h"

ItemFactory::ItemFactory(IResourceManager& resourceManager) : _resourceManager(resourceManager) {
}

std::shared_ptr<IItem> ItemFactory::buildItem(std::string itemId, Vector2& position, double orientation, std::string& texture)
{
	if (itemId == "SIGSAUER") {
		int width = 32;
		int height = 32;
		std::shared_ptr<StaticRenderable> itemRenderable = std::make_shared<StaticRenderable>(position, width, height, orientation, _resourceManager, texture);
		return std::make_shared<Firearm>(20, 30, 20, 60, 1, position, 32, 32, orientation, itemRenderable);
	}

	return NULL;
}
