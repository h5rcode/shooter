#include "LevelDescriptor.h"

#include <fstream>
#include <SFML/Graphics.hpp>

#include "json.hpp"

#include "Vector2.h"

using nlohmann::json;

using namespace Shooter::Items;
using namespace Shooter::LevelDescriptors;
using namespace Shooter::WorldDatabase::Props;

LevelDescriptor::LevelDescriptor(ItemFactory& itemFactory, IPropDatabase& propDatabase) :
	_itemFactory(itemFactory),
	_propDatabase(propDatabase) {
}

std::vector<std::shared_ptr<IItem>> LevelDescriptor::getItems() {
	std::vector<std::shared_ptr<IItem>> items;

	for (std::vector<std::shared_ptr<LevelItemDescriptor>>::iterator it = this->itemDescriptors.begin(); it != this->itemDescriptors.end(); ++it)
	{
		std::shared_ptr<LevelItemDescriptor> itemDescriptor = *it;

		Vector2 position(itemDescriptor->x, itemDescriptor->y);
		double orientation = itemDescriptor->orientation;
		std::string itemId = itemDescriptor->itemId;

		std::shared_ptr<IItem> item = _itemFactory.buildItem(itemId, position, orientation);
		items.push_back(item);
	}

	return items;
}

std::vector<std::shared_ptr<Prop>> LevelDescriptor::getProps() {
	std::vector<std::shared_ptr<Prop>> props;
	for (std::vector<std::shared_ptr<LevelPropDescriptor>>::iterator it = this->propDescriptors.begin(); it != this->propDescriptors.end(); ++it)
	{
		std::shared_ptr<LevelPropDescriptor> levelPropDescriptor = *it;
		PropDescriptor& propDescriptor = _propDatabase.getProp(levelPropDescriptor->propId);

		Vector2 position(levelPropDescriptor->x, levelPropDescriptor->y);
		double orientation = levelPropDescriptor->orientation;

		std::shared_ptr<Prop> prop = std::make_shared<Prop>(
			levelPropDescriptor->propId,
			propDescriptor.name,
			position,
			propDescriptor.width,
			propDescriptor.height,
			orientation);

		props.push_back(prop);
	}

	return props;
}

std::vector<std::shared_ptr<Wall>> LevelDescriptor::getWalls() {
	std::vector<std::shared_ptr<Wall>> walls;
	for (std::vector<std::shared_ptr<WallDescriptor>>::iterator it = this->wallDescriptors.begin(); it != this->wallDescriptors.end(); ++it)
	{
		std::shared_ptr<WallDescriptor> wallDescriptor = *it;

		Vector2 position(wallDescriptor->x, wallDescriptor->y);
		double orientation = wallDescriptor->orientation;
		int width = wallDescriptor->width;
		int length = wallDescriptor->length;

		std::shared_ptr<Wall> wall = std::make_shared<Wall>(position, width, length, orientation, wallDescriptor->texture);
		walls.push_back(wall);
	}

	return walls;
}

void LevelDescriptor::loadFromFile(std::string& fileName) {
	std::ifstream fileStream(fileName);

	json jsonObject;
	fileStream >> jsonObject;

	this->name = jsonObject.at("name").get<std::string>();

	json::value_type walls = jsonObject.at("walls");
	for (json::iterator it = walls.begin(); it != walls.end(); ++it)
	{
		WallDescriptor wd = *it;
		std::shared_ptr<WallDescriptor> wallDescriptor = std::make_shared<WallDescriptor>(wd);

		this->wallDescriptors.push_back(wallDescriptor);
	}

	json::value_type props = jsonObject.at("props");
	for (json::iterator it = props.begin(); it != props.end(); ++it)
	{
		LevelPropDescriptor ld = *it;
		std::shared_ptr<LevelPropDescriptor> propDescriptor = std::make_shared<LevelPropDescriptor>(ld);

		this->propDescriptors.push_back(propDescriptor);
	}

	json::value_type items = jsonObject.at("items");
	for (json::iterator it = items.begin(); it != items.end(); ++it)
	{
		LevelItemDescriptor id = *it;
		std::shared_ptr<LevelItemDescriptor> itemDescriptor = std::make_shared<LevelItemDescriptor>(id);

		this->itemDescriptors.push_back(itemDescriptor);
	}

	json::value_type playerInitialState = jsonObject.at("playerInitialState");
	this->playerInitialStateDescriptor.x = playerInitialState.at("x").get<double>();
	this->playerInitialStateDescriptor.y = playerInitialState.at("y").get<double>();
}