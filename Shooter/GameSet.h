#pragma once

#include "IGameSet.h"
#include "Prop.h"
#include "Wall.h"

class GameSet : public IGameSet
{
public:
	GameSet();
public:
	bool collidesWith(Player & player) const;
	std::vector<std::shared_ptr<Wall>>& getWalls();
	std::vector<std::shared_ptr<Prop>>& getProps();
private:
	std::vector<std::shared_ptr<Wall>> _walls;
	std::vector<std::shared_ptr<Prop>> _props;
};

