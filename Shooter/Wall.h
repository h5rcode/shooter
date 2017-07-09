#pragma once

#include <string>

#include "Player.h"
#include "Vector2.h"

class Wall {
public:
	Wall(Vector2 start, Vector2 end, std::string texture);
public:
	Vector2& getStart();
	Vector2& getEnd();
	std::string& getTexture();
	bool collidesWith(Player& player) const;
private:
	Vector2 _start;
	Vector2 _end;
	std::string _texture;
};