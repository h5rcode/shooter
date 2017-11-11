#pragma once

#include <SFML/Graphics.hpp>

#include "IRenderer.h"

class SfmlRenderer : public IRenderer
{
public:
	SfmlRenderer(sf::RenderWindow& window);

	void render(IGameState& gameState);
	void quit();

private:
	sf::RenderWindow& _window;
};

