#pragma once

#include <SFML/Graphics.hpp>

#include "AnimatedSprite.h"
#include "Animation.h"
#include "IAnimatedRenderable.h"

class AnimatedRenderable : public IAnimatedRenderable
{
public:
	AnimatedRenderable();

	void play();
	void pause();
	void render(sf::RenderWindow& renderWindow);
	void setRotation(double rotation);
	void setPosition(double x, double y);
	void update(sf::Time elapsedTime);
private:
	sf::Texture _texture;
	Animation _animation;
	AnimatedSprite _animatedSprite;
};

