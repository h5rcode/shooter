#pragma once

#include <SFML/Graphics.hpp>

#include "IGameState.h"
#include "IRenderer.h"

class SfmlRenderer : public IRenderer
{
public:
	SfmlRenderer(IGameState& gameState, sf::RenderWindow& window);

	void render();

private:
	IGameState& _gameState;
	sf::RenderWindow& _window;

private:
	void renderHud();
};

