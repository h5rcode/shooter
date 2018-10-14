#pragma once

#include <memory>
#include <string>

#include "IItem.h"
#include "IItemDatabase.h"
#include "IResourceManager.h"
#include "Vector2.h"

class ItemFactory
{
public:
	ItemFactory(IItemDatabase& itemDatabase, IResourceManager& resourceManager);

public:
	std::shared_ptr<IItem> buildItem(std::string itemId, Vector2& position, double orientation, std::string textureFilename);

private:
	IItemDatabase& _itemDatabase;
	IResourceManager& _resourceManager;
};

