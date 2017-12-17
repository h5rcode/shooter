#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "BoundingBox.h"
#include "Vector2.h"

class Prop {
public:
	Prop(Vector2 position, int width, int height, double orientation, std::string& texture);
public:
	BoundingBox & getBoundingBox();
	Vector2& getPosition();
	void render(sf::RenderWindow& renderWindow);
private:
	BoundingBox _boundingBox;
	double _orientation;
	Vector2 _position;
	sf::Texture _texture;
	sf::Sprite _sprite;
};