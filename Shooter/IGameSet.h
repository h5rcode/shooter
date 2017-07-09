#pragma once

#include <list>

#include "Player.h"
#include "Prop.h"
#include "Wall.h"

class IGameSet {
public:
	virtual bool collidesWith(Player& player) const = 0;
	virtual std::list<Wall>& getWalls() = 0;
	virtual std::list<Prop>& getProps() = 0;
};