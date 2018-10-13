#include "Firearm.h"
#include "ItemFactory.h"
#include "StaticRenderable.h"

ItemFactory::ItemFactory(IResourceManager& resourceManager) : _resourceManager(resourceManager) {
}

std::shared_ptr<IItem> ItemFactory::buildItem(std::string itemId, Vector2& position, double orientation, std::string textureFilename)
{
	if (itemId == "SIGSAUER") {
		int width = 32;
		int height = 32;
		sf::Texture* texture = _resourceManager.getTexture(textureFilename);

		std::shared_ptr<StaticRenderable> itemRenderable = std::make_shared<StaticRenderable>(position, width, height, orientation, *texture);
		return std::make_shared<Firearm>("Sig-Sauer", 20, 30, 20, 60, 1, position, 32, 32, orientation, _resourceManager, itemRenderable);
	}

	return NULL;
}
