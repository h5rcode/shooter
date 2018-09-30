#pragma once

#include "gmock/gmock.h"

#include "IInventory.h"

class InventoryMock : public IInventory {
public:
	MOCK_METHOD1(addItem, bool(std::shared_ptr<IItem> item));
	MOCK_CONST_METHOD0(getCurrentWeight, int());
	MOCK_CONST_METHOD0(getMaxWeight, int());
};