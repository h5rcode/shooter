#include "GameSet.h"

GameSet::GameSet()
{
	_walls = std::vector<std::shared_ptr<Wall>>();

	std::string wallTexture = "Resources/textures/wall-01.png";

	Vector2 position1(300, 500);
	Vector2 position2(200, 256);

	_walls.push_back(std::make_shared<Wall>(position1, 30, 100, 0.5, wallTexture));
	_walls.push_back(std::make_shared<Wall>(position2, 100, 1000, 0, wallTexture));
}

bool GameSet::collidesWith(Player& player) const {

	for (std::vector<std::shared_ptr<Wall>>::const_iterator iterator = _walls.begin(); iterator != _walls.end(); iterator++)
	{
		std::shared_ptr<Wall> wall = *iterator;

		if (wall->collidesWith(player)) {
			return true;
		}
	}

	for (std::vector<std::shared_ptr<Prop>>::const_iterator iterator = _props.begin(); iterator != _props.end(); iterator++) {
		std::shared_ptr<Prop> prop = *iterator;

		if (prop->collidesWith(player)) {
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
