#include "SfmlInputManager.h"

#include <SFML/Graphics.hpp>

#include <stdexcept>

using namespace Shooter::Input;

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

bool SfmlInputManager::pollEvent(sf::Event& event) {
	return _window.pollEvent(event);
}
