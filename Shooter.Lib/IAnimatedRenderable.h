#pragma once

#include <SFML/Graphics.hpp>

class IAnimatedRenderable {
public:
	virtual void pause() = 0;
	virtual void play() = 0;
	virtual void render(sf::RenderWindow& renderWindow) = 0;
	virtual void setPosition(double x, double y) = 0;
	virtual void setRotation(double rotation) = 0;
	virtual void update(sf::Time elapsedTime) = 0;
};