#pragma once

#include "IItem.h"

class IInventory {

public:
	virtual bool addItem(std::shared_ptr<IItem> item) = 0;
	virtual int getCurrentWeight() const = 0;
	virtual int getMaxWeight() const = 0;
};