#pragma once

#include <string>
#include "Vector2.h"

class Crosshair
{
public:
	Crosshair(std::string& texture);

	Vector2& getPosition();
	std::string& getTexture();

private:
	std::string& _texture;
	Vector2 _position;
};

