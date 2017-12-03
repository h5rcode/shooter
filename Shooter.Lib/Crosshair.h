#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include "Vector2.h"

class Crosshair
{
public:
	Crosshair(std::string& texture);

	Vector2& getPosition();

	void render(sf::RenderWindow& renderWindow);

private:
	sf::Texture _texture;
	sf::Sprite _sprite;

	Vector2 _position;
};

