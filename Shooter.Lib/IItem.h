#pragma once

#include "BoundingBox.h"

class IItem
{
public:
	virtual BoundingBox& getBoundingBox() const = 0;
	virtual int getWeight() const = 0;
	virtual void setSelected(bool selected) = 0;
};

