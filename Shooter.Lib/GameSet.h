#pragma once

#include "IGameSet.h"

class GameSet : public IGameSet
{
public:
	GameSet();
public:
	bool collidesWith(BoundingBox& boundingBox) const;
	std::vector<std::shared_ptr<Wall>>& getWalls();
	std::vector<std::shared_ptr<Prop>>& getProps();
	void render(sf::RenderWindow& renderWindow);
private:
	std::vector<std::shared_ptr<Wall>> _walls;
	std::vector<std::shared_ptr<Prop>> _props;
};

