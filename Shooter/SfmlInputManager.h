#pragma once

#include <SFML/Graphics.hpp>

#include "IInputManager.h"

class SfmlInputManager : public IInputManager
{
public:
	SfmlInputManager(sf::RenderWindow &window);

	void getMouseState(int& mouseX, int& mouseY);
	bool isKeyDown(Key key);
	bool pollEvent(Event& event);

private:
	sf::RenderWindow& _window;

private:
	sf::Keyboard::Key getSfmlKey(Key key) const;
};

