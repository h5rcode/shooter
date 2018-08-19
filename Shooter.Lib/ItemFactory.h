#pragma once

#include <memory>
#include <string>

#include "IItem.h"
#include "Vector2.h"

class ItemFactory
{
public:
	std::shared_ptr<IItem> buildItem(std::string itemId, Vector2& position, double orientation, std::string& texture);
};

