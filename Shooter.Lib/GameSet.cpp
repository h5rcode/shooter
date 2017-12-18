#include "GameSet.h"

GameSet::GameSet(std::vector<std::shared_ptr<Wall>> walls, std::vector<std::shared_ptr<Prop>> props)
{
	_walls = walls;
	_props = props;
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

void GameSet::render(sf::RenderWindow& renderWindow)
{
	for (std::vector<std::shared_ptr<Wall>>::iterator it = _walls.begin(); it != _walls.end(); ++it)
	{
		std::shared_ptr<Wall> wall = *it;
		wall->render(renderWindow);
	}

	for (std::vector<std::shared_ptr<Prop>>::iterator it = _props.begin(); it != _props.end(); ++it)
	{
		std::shared_ptr<Prop> prop = *it;
		prop->render(renderWindow);
	}
}
