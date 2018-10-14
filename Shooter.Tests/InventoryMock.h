#pragma once

#include "gmock/gmock.h"

#include "IInventory.h"

using namespace Shooter::Inventory;

class InventoryMock : public IInventory {
public:
	MOCK_METHOD1(addItem, bool(std::shared_ptr<IItem> item));
	MOCK_CONST_METHOD0(getCurrentWeight, int());
	MOCK_METHOD0(getItems, std::vector<std::shared_ptr<IItem>>&());
	MOCK_CONST_METHOD0(getMaxWeight, int());
};