#pragma once

#include "IStaticRenderable.h"
#include "Vector2.h"

class StaticRenderable : public IStaticRenderable {
public:
	StaticRenderable(Vector2 position, int width, int height, double orientation, std::string& texture);

public:
	void render(sf::RenderWindow& renderWindow) override;

private:
	int _width;
	int _height;
	Vector2 _position;
	double _orientation;
	sf::Texture _texture;
	sf::Sprite _sprite;
};