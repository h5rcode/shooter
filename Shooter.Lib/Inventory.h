#pragma once

#include <memory>
#include <vector>

#include "IItem.h"
#include "IInventory.h"

class Inventory : public IInventory
{
public:
	Inventory();

public:
	bool addItem(std::shared_ptr<IItem> item);

private:
	std::vector<std::shared_ptr<IItem>> _items;

	int _currentWeight;
	int _maxWeight;
};

