#include "LevelDescriptor.h"

#include <fstream>
#include <SFML/Graphics.hpp>

#include "json.hpp"

#include "Vector2.h"

using nlohmann::json;

using namespace Shooter::Items;
using namespace Shooter::LevelDescriptors;

const std::string TEXTURES_PATH = "Resources/textures/";

LevelDescriptor::LevelDescriptor(ItemFactory& itemFactory, IResourceManager& resourceManager)
	: _itemFactory(itemFactory), _resourceManager(resourceManager) {
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
	for (std::vector<std::shared_ptr<PropDescriptor>>::iterator it = this->propDescriptors.begin(); it != this->propDescriptors.end(); ++it)
	{
		std::shared_ptr<PropDescriptor> propDescriptor = *it;

		Vector2 position(propDescriptor->x, propDescriptor->y);
		double orientation = propDescriptor->orientation;
		int width = propDescriptor->width;
		int height = propDescriptor->height;

		std::shared_ptr<Prop> prop = std::make_shared<Prop>(position, width, height, orientation, propDescriptor->texture);
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

	json json;
	fileStream >> json;

	this->name = json.at("name").get<std::string>();

	json::value_type walls = json.at("walls");
	for (json::iterator it = walls.begin(); it != walls.end(); ++it)
	{
		json::value_type wall = *it;

		std::shared_ptr<WallDescriptor> wallDescriptor = std::make_shared<WallDescriptor>();
		wallDescriptor->x = wall.at("x").get<double>();
		wallDescriptor->y = wall.at("y").get<double>();
		wallDescriptor->orientation = wall.at("orientation").get<double>();
		wallDescriptor->texture = TEXTURES_PATH + wall.at("texture").get<std::string>();
		wallDescriptor->width = wall.at("width").get<int>();
		wallDescriptor->length = wall.at("length").get<int>();

		this->wallDescriptors.push_back(wallDescriptor);
	}

	json::value_type props = json.at("props");
	for (json::iterator it = props.begin(); it != props.end(); ++it)
	{
		json::value_type prop = *it;

		std::shared_ptr<PropDescriptor> propDescriptor = std::make_shared<PropDescriptor>();
		propDescriptor->x = prop.at("x").get<double>();
		propDescriptor->y = prop.at("y").get<double>();
		propDescriptor->orientation = prop.at("orientation").get<double>();
		propDescriptor->texture = TEXTURES_PATH + prop.at("texture").get<std::string>();
		propDescriptor->width = prop.at("width").get<int>();
		propDescriptor->height = prop.at("height").get<int>();

		this->propDescriptors.push_back(propDescriptor);
	}

	json::value_type items = json.at("items");
	for (json::iterator it = items.begin(); it != items.end(); ++it)
	{
		json::value_type item = *it;

		std::shared_ptr<LevelItemDescriptor> itemDescriptor = std::make_shared<LevelItemDescriptor>();
		itemDescriptor->itemId = item.at("itemId").get<std::string>();
		itemDescriptor->x = item.at("x").get<double>();
		itemDescriptor->y = item.at("y").get<double>();
		itemDescriptor->orientation = item.at("orientation").get<double>();

		this->itemDescriptors.push_back(itemDescriptor);
	}

	json::value_type playerInitialState = json.at("playerInitialState");
	this->playerInitialStateDescriptor.x = playerInitialState.at("x").get<double>();
	this->playerInitialStateDescriptor.y = playerInitialState.at("y").get<double>();
}