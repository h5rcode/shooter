#include "GameSet.h"

GameSet::GameSet()
{
	_walls = std::list<Wall>();

	std::string wallTexture = "D:\\Projets\\shooter\\Resources\\img\\wall-01.png";

	Vector2 s1(100, 0);
	Vector2 e1(100, 256);
	Vector2 s2(100, 256);
	Vector2 e2(356, 256);

	_walls.push_back(Wall(s1, e1, wallTexture));
	_walls.push_back(Wall(s2, e2, wallTexture));
}

bool GameSet::collidesWith(Player& player) const {

	for (std::list<Wall>::const_iterator iterator = _walls.begin(); iterator != _walls.end(); iterator++)
	{
		Wall wall = *iterator;

		if (wall.collidesWith(player)) {
			return true;
		}
	}

	for (std::list<Prop>::const_iterator iterator = _props.begin(); iterator != _props.end(); iterator++) {
		Prop prop = *iterator;

		if (prop.collidesWith(player)) {
			return true;
		}
	}

	return false;
}

std::list<Wall>& GameSet::getWalls()
{
	return _walls;
}

std::list<Prop>& GameSet::getProps()
{
	return _props;
}
