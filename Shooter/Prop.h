#pragma once

#include <string>

#include "Player.h"
#include "Vector2.h"

class Prop {
public:
	Prop(std::string& texture);
public:
	bool collidesWith(Player& player) const;
	Vector2& getPosition();
	std::string& getTexture();
private:
	Vector2 _position;
	std::string& _texture;
};