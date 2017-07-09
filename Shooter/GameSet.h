#pragma once

#include "IGameSet.h"
#include "Prop.h"
#include "Wall.h"

#include <list>

class GameSet : public IGameSet
{
public:
	GameSet();
public:
	bool collidesWith(Player & player) const;
	std::list<Wall>& getWalls();
	std::list<Prop>& getProps();
private:
	std::list<Wall> _walls;
	std::list<Prop> _props;
};

