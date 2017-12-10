#include "SfmlInputManager.h"

#include <SFML/Graphics.hpp>

#include <stdexcept>

SfmlInputManager::SfmlInputManager(sf::RenderWindow &window)
	: _window(window)
{
}

void SfmlInputManager::getMouseState(double& mouseX, double& mouseY) {
	sf::Vector2i mousePosition = sf::Mouse::getPosition(_window);

	sf::Vector2f worldPosition = _window.mapPixelToCoords(mousePosition);

	mouseX = (double)worldPosition.x;
	mouseY = (double)worldPosition.y;
}

bool SfmlInputManager::isKeyDown(Key key) {
	sf::Keyboard::Key sfmlKey = getSfmlKey(key);
	return sf::Keyboard::isKeyPressed(sfmlKey);
}

bool SfmlInputManager::pollEvent(Event& event) {
	sf::Event sfmlEvent;
	bool pendingEventAvailable = _window.pollEvent(sfmlEvent);

	if (pendingEventAvailable)
	{
		switch (sfmlEvent.type)
		{
		case sf::Event::MouseButtonPressed:
			event.setType(MOUSE_BUTTON_DOWN);
			break;

		case sf::Event::Closed:
			event.setType(QUIT);
			break;

		default:
			break;
		}
	}

	return pendingEventAvailable == 1;
}

sf::Keyboard::Key SfmlInputManager::getSfmlKey(Key key) const {
	switch (key)
	{
	case DOWN:
		return sf::Keyboard::S;

	case LEFT:
		return sf::Keyboard::Q;

	case RIGHT:
		return sf::Keyboard::D;

	case UP:
		return sf::Keyboard::Z;
	}

	throw std::invalid_argument("Invalid key.");
}