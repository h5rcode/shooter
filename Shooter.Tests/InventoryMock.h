#pragma once

#include "gmock/gmock.h"

#include "IInventory.h"

class InventoryMock : public IInventory {
public:
	MOCK_METHOD1(addItem, bool(std::shared_ptr<IItem> item));
};