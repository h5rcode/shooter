#include "GameSet.h"

GameSet::GameSet()
{
	_walls = std::vector<std::shared_ptr<Wall>>();

	std::string wallTexture = "Resources/textures/wall-01.png";

	Vector2 position1(256, 256);
	Vector2 position2(512, 512);

	_walls.push_back(std::make_shared<Wall>(position1, 64, 512, 35, wallTexture));
	_walls.push_back(std::make_shared<Wall>(position2, 32, 256, -15, wallTexture));
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

std::vector<std::shared_ptr<Wall>>& GameSet::getWalls()
{
	return _walls;
}

std::vector<std::shared_ptr<Prop>>& GameSet::getProps()
{
	return _props;
}

void GameSet::render(sf::RenderWindow& renderWindow)
{
	for (std::vector<std::shared_ptr<Wall>>::iterator it = _walls.begin(); it != _walls.end(); ++it)
	{
		std::shared_ptr<Wall> wall = *it;
		wall->render(renderWindow);
	}
}
