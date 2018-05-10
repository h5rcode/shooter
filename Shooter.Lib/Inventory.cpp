#include "Inventory.h"

const int MAX_WEIGHT = 100;

Inventory::Inventory() :
	_items(),
	_currentWeight(0),
	_maxWeight(MAX_WEIGHT)
{
}

bool Inventory::addItem(std::shared_ptr<IItem> item) {
	int newWeight = _currentWeight + item->getWeight();
	if (newWeight > _maxWeight) {
		return false;
	}

	_items.push_back(item);
	return true;
}

