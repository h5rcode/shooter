#pragma once

#include <memory>
#include <string>

#include "IItem.h"
#include "IResourceManager.h"
#include "Vector2.h"

class ItemFactory
{
public:
	ItemFactory(IResourceManager& resourceManager);

public:
	std::shared_ptr<IItem> buildItem(std::string itemId, Vector2& position, double orientation, std::string texture);

private:
	IResourceManager& _resourceManager;
};

