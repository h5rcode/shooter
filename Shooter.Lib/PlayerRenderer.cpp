#include "PlayerRenderer.h"

using namespace Shooter::Rendering::Renderers;

const int FRAME_WIDTH = 64;
const int FRAME_HEIGHT = 64;
const int NUMBER_OF_FRAMES = 8;
const int FRAME_TIME_MILLISECONDS = 150;

PlayerRenderer::PlayerRenderer(sf::RenderWindow& renderWindow, sf::Texture& texture) :
	_renderWindow(renderWindow) {

	_animation.setSpriteSheet(texture);
	for (int frameNumber = 0; frameNumber < NUMBER_OF_FRAMES; frameNumber++) {
		_animation.addFrame(sf::IntRect(0, frameNumber * FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT));
	}

	_animatedSprite.setAnimation(_animation);
	_animatedSprite.setOrigin(FRAME_WIDTH / 2, FRAME_HEIGHT / 2);
	_animatedSprite.setFrameTime(sf::milliseconds(FRAME_TIME_MILLISECONDS));
}


void PlayerRenderer::render(IPlayer& player, sf::Time elapsedTime) {
	Vector2& position = player.getPosition();
	Vector2& speed = player.getSpeed();

	if (speed == Vector2(0, 0)) {
		if (_animatedSprite.isPlaying()) {
			_animatedSprite.pause();
		}
	}
	else {
		if (_animatedSprite.isPlaying() == false) {
			_animatedSprite.play();
		}

		_animatedSprite.update(elapsedTime);
	}

	_animatedSprite.setRotation((float)player.getOrientation());
	_animatedSprite.setPosition((float)position.x, (float)position.y);

	_renderWindow.draw(_animatedSprite);
}