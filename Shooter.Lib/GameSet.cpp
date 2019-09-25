#include "GameSet.h"

using namespace Shooter::Math;
using namespace Shooter::World;

GameSet::GameSet(
	std::vector<std::shared_ptr<Floor>> floors,
	std::vector<std::shared_ptr<IItem>> items,
	std::vector<std::shared_ptr<Wall>> walls,
	std::vector<std::shared_ptr<Prop>> props)
{
	_floors = floors;
	_items = items;
	_walls = walls;
	_props = props;
}

void GameSet::addProp(std::shared_ptr<Prop> prop) {
	_props.push_back(prop);
}

bool GameSet::collidesWith(BoundingBox& boundingBox) const {

	for (std::vector<std::shared_ptr<Wall>>::const_iterator iterator = _walls.begin(); iterator != _walls.end(); iterator++)
	{
		std::shared_ptr<Wall> wall = *iterator;
		BoundingBox& wallBoundingBox = wall->getBoundingBox();

		if (wallBoundingBox.intersects(boundingBox)) {
			return true;
		}
	}

	for (std::vector<std::shared_ptr<Prop>>::const_iterator iterator = _props.begin(); iterator != _props.end(); iterator++)
	{
		std::shared_ptr<Prop> prop = *iterator;
		BoundingBox& propBoundingBox = prop->getBoundingBox();

		if (propBoundingBox.intersects(boundingBox)) {
			return true;
		}
	}

	return false;
}

std::vector<std::shared_ptr<Floor>>& GameSet::getFloors() {
	return _floors;
}

std::shared_ptr<IItem> GameSet::getItemAt(Vector2& position) {
	BoundingBox boundingBox(position, 1, 1, 0);
	for (std::vector<std::shared_ptr<IItem>>::const_iterator iterator = _items.begin(); iterator != _items.end(); iterator++)
	{
		std::shared_ptr<IItem> item = *iterator;
		BoundingBox& itemBoundingBox = item->getBoundingBox();

		if (itemBoundingBox.intersects(boundingBox)) {
			return item;
		}
	}

	return NULL;
}

std::vector<std::shared_ptr<IItem>>& GameSet::getItems() {
	return _items;
}

std::shared_ptr<Prop> GameSet::getPropAt(Vector2& position) {
	BoundingBox boundingBox(position, 1, 1, 0);
	for (std::vector<std::shared_ptr<Prop>>::const_iterator iterator = _props.begin(); iterator != _props.end(); iterator++)
	{
		std::shared_ptr<Prop> prop = *iterator;
		BoundingBox& propBoundingBox = prop->getBoundingBox();

		if (propBoundingBox.intersects(boundingBox)) {
			return prop;
		}
	}

	return NULL;
}

std::vector<std::shared_ptr<Prop>>& GameSet::getProps()
{
	return _props;
}

std::vector<std::shared_ptr<Wall>>& GameSet::getWalls()
{
	return _walls;
}

void GameSet::removeItem(std::shared_ptr<IItem> item) {
	std::vector<std::shared_ptr<IItem>>::const_iterator position = std::find(_items.begin(), _items.end(), item);

	if (position != _items.end()) {
		_items.erase(position);
	}
}

void GameSet::removeProp(std::shared_ptr<Prop> prop) {
	std::vector<std::shared_ptr<Prop>>::const_iterator position = std::find(_props.begin(), _props.end(), prop);

	if (position != _props.end()) {
		_props.erase(position);
	}
}

std::vector<std::shared_ptr<Collision>> GameSet::computeCollisionsWithSegment(Vector2& segmentOrigin, Vector2& segmentEnd) {
	std::vector<std::shared_ptr<Collision>> collisions;

	for each (std::shared_ptr<Wall> wall in _walls)
	{
		BoundingBox& wallBoundingBox = wall->getBoundingBox();
		std::vector<std::shared_ptr<Collision>> wallCollisions = wallBoundingBox.computeCollisionsWithSegment(segmentOrigin, segmentEnd);

		for each (std::shared_ptr<Collision> wallCollision in wallCollisions)
		{
			collisions.push_back(wallCollision);
		}
	}

	for each (std::shared_ptr<Prop> prop in _props)
	{
		BoundingBox& propBoundingBox = prop->getBoundingBox();
		std::vector<std::shared_ptr<Collision>> propCollisions = propBoundingBox.computeCollisionsWithSegment(segmentOrigin, segmentEnd);

		for each (std::shared_ptr<Collision> propCollision in propCollisions)
		{
			collisions.push_back(propCollision);
		}
	}

	return collisions;
}