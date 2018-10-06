#pragma once

#include <SFML/Graphics.hpp>

#include "AnimatedSprite.h"
#include "Animation.h"
#include "IAnimatedRenderable.h"
#include "IResourceManager.h"

class AnimatedRenderable : public IAnimatedRenderable
{
public:
	AnimatedRenderable(IResourceManager& resourceManager);

	void play();
	void pause();
	void render(sf::RenderWindow& renderWindow);
	void setRotation(double rotation);
	void setPosition(double x, double y);
	void update(sf::Time elapsedTime);
private:
	Animation _animation;
	AnimatedSprite _animatedSprite;
	IResourceManager& _resourceManager;
};

