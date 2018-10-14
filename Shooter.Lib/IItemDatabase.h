#pragma once

#include "ItemDescriptor.h"

class IItemDatabase {
public:
	virtual ItemDescriptor& getItem(std::string& id) = 0;
};