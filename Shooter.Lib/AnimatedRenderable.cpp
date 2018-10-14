#include "AnimatedRenderable.h"

using namespace Shooter::Rendering::Renderables;

const int FRAME_WIDTH = 64;
const int FRAME_HEIGHT = 64;
const int NUMBER_OF_FRAMES = 8;
const int FRAME_TIME_MILLISECONDS = 150;

AnimatedRenderable::AnimatedRenderable(sf::Texture& texture) :
	_animatedSprite(),
	_animation()
{
	_animation.setSpriteSheet(texture);
	for (int frameNumber = 0; frameNumber < NUMBER_OF_FRAMES; frameNumber++) {
		_animation.addFrame(sf::IntRect(0, frameNumber * FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT));
	}

	_animatedSprite.setAnimation(_animation);
	_animatedSprite.setOrigin(FRAME_WIDTH / 2, FRAME_HEIGHT / 2);
	_animatedSprite.setFrameTime(sf::milliseconds(FRAME_TIME_MILLISECONDS));
}

void AnimatedRenderable::play()
{
	_animatedSprite.play();
}

void AnimatedRenderable::pause()
{
	_animatedSprite.pause();
}

void AnimatedRenderable::render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(_animatedSprite);
}

void AnimatedRenderable::setPosition(double x, double y)
{
	_animatedSprite.setPosition((float)x, (float)y);
}

void AnimatedRenderable::setRotation(double rotation)
{
	_animatedSprite.setRotation((float)rotation);
}

void AnimatedRenderable::update(sf::Time elapsedTime)
{
	_animatedSprite.update(elapsedTime);
}
