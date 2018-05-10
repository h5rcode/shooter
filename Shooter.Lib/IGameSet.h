#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

#include "BoundingBox.h"
#include "IItem.h"
#include "Prop.h"
#include "Vector2.h"
#include "Wall.h"

class IGameSet {
public:
	virtual void addProp(std::shared_ptr<Prop> prop) = 0;
	virtual bool collidesWith(BoundingBox& boundingBox) const = 0;
	virtual std::shared_ptr<IItem> getItemAt(Vector2& position) = 0;
	virtual std::shared_ptr<Prop> getPropAt(Vector2& position) = 0;
	virtual std::vector<std::shared_ptr<Prop>>& getProps() = 0;
	virtual std::vector<std::shared_ptr<Wall>>& getWalls() = 0;
	virtual void removeProp(std::shared_ptr<Prop> prop) = 0;
	virtual void render(sf::RenderWindow& renderWindow) = 0;
};