#pragma once

#include <SFML/Graphics.hpp>

#include "IGameState.h"
#include "IRenderer.h"

class SfmlRenderer : public IRenderer
{
public:
	SfmlRenderer(IGameState& gameState, sf::RenderWindow& window);

public:
	void render();

private:
	void renderHud();

private:
	IGameState& _gameState;
	sf::RenderWindow& _window;
	sf::Font _font;
};

