#include "Inventory.h"

const int MAX_WEIGHT = 100;

Inventory::Inventory() :
	_items(),
	_currentWeight(0),
	_maxWeight(MAX_WEIGHT)
{
}

Inventory::Inventory(int maxWeight) :
	_items(),
	_currentWeight(0),
	_maxWeight(maxWeight)
{
}

bool Inventory::addItem(std::shared_ptr<IItem> item) {
	int itemWeight = item->getWeight();
	int newWeight = _currentWeight + itemWeight;
	if (newWeight > _maxWeight) {
		return false;
	}

	_items.push_back(item);
	_currentWeight += itemWeight;

	return true;
}

int Inventory::getCurrentWeight() const {
	return _currentWeight;
}

std::vector<std::shared_ptr<IItem>>& Inventory::getItems() {
	return _items;
}

int Inventory::getMaxWeight() const {
	return _maxWeight;
}
