#pragma once

#include "IGameSet.h"

class GameSet : public IGameSet
{
public:
	GameSet(std::vector<std::shared_ptr<IItem>> items, std::vector<std::shared_ptr<Wall>> walls, std::vector<std::shared_ptr<Prop>> props);
public:
	void addProp(std::shared_ptr<Prop> prop);
	bool collidesWith(BoundingBox& boundingBox) const;
	std::vector<std::shared_ptr<Prop>>& getProps();
	std::shared_ptr<IItem> getItemAt(Vector2& position);
	std::shared_ptr<Prop> getPropAt(Vector2& position);
	std::vector<std::shared_ptr<Wall>>& getWalls();
	void removeProp(std::shared_ptr<Prop> prop);
	void render(sf::RenderWindow& renderWindow);
private:
	std::vector<std::shared_ptr<IItem>> _items;
	std::vector<std::shared_ptr<Wall>> _walls;
	std::vector<std::shared_ptr<Prop>> _props;
};

