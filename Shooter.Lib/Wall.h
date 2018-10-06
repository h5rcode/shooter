#pragma once

#include <SFML/Graphics.hpp>

#include <string>

#include "BoundingBox.h"
#include "Vector2.h"

class Wall {
public:
	Wall(Vector2 position, int width, int length, double orientation, sf::Texture& texture);
public:
	BoundingBox& getBoundingBox();
	Vector2& getPosition();
	int getWidth() const;
	int getLength() const;
	double getOrientation() const;
	void render(sf::RenderWindow& renderWindow);
private:
	BoundingBox _boundingBox;
	Vector2 _position;
	int _width;
	int _length;
	double _orientation;
	sf::Sprite _sprite;
};