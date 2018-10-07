#pragma once

#include "gmock/gmock.h"

#include "IItem.h"

class ItemMock : public IItem {
public:
	MOCK_METHOD0(getBoundingBox, BoundingBox& ());
	MOCK_METHOD0(getName, std::string&());
	MOCK_METHOD0(getPosition, Vector2& ());
	MOCK_CONST_METHOD0(getWeight, int());
	MOCK_METHOD1(setSelected, void(bool selected));
	MOCK_METHOD1(render, void(sf::RenderWindow& renderWindow));
};