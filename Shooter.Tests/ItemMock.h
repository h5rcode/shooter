#pragma once

#include "gmock/gmock.h"

#include "IItem.h"

using namespace Shooter::Math;

class ItemMock : public IItem {
public:
	MOCK_METHOD0(getBoundingBox, BoundingBox& ());
	MOCK_CONST_METHOD0(getHeight, int());
	MOCK_METHOD0(getId, std::string&());
	MOCK_METHOD0(getName, std::string&());
	MOCK_CONST_METHOD0(getOrientation, double());
	MOCK_METHOD0(getPosition, Vector2& ());
	MOCK_CONST_METHOD0(getWeight, int());
	MOCK_CONST_METHOD0(getWidth, int());
	MOCK_METHOD1(setSelected, void(bool selected));
};