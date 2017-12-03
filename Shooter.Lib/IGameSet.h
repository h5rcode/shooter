#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

#include "BoundingBox.h"
#include "Prop.h"
#include "Wall.h"

class IGameSet {
public:
	virtual bool collidesWith(BoundingBox& boundingBox) const = 0;
	virtual std::vector<std::shared_ptr<Wall>>& getWalls() = 0;
	virtual std::vector<std::shared_ptr<Prop>>& getProps() = 0;
	virtual void render(sf::RenderWindow& renderWindow) = 0;
};