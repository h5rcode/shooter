#pragma once

#include <string>

#include "Player.h"
#include "Vector2.h"

class Wall {
public:
	Wall(Vector2 position, int width, int length, double orientation, std::string texture);
public:
	Vector2& getPosition();
	int getWidth() const;
	int getLength() const;
	double getOrientation() const;
	std::string& getTexture();
	bool collidesWith(Player& player) const;
private:
	Vector2 _position;
	int _width;
	int _length;
	double _orientation;
	std::string _texture;
};