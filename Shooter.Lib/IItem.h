#pragma once

#include "BoundingBox.h"

#include <SFML/Graphics.hpp>

class IItem
{
public:
	virtual BoundingBox& getBoundingBox() = 0;
	virtual Vector2& getPosition() = 0;
	virtual int getWeight() const = 0;
	virtual void setSelected(bool selected) = 0;
	virtual void render(sf::RenderWindow& renderWindow) = 0;
};

