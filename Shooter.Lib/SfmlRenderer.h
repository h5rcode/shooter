#pragma once

#include <SFML/Graphics.hpp>

#include "IGameState.h"
#include "IRenderer.h"
#include "IResourceManager.h"

class SfmlRenderer : public IRenderer
{
public:
	SfmlRenderer(IGameState& gameState, sf::RenderWindow& window, IResourceManager& resourceManager);

public:
	void render();

private:
	void renderHud();

private:
	IGameState& _gameState;
	IResourceManager& _resourceManager;
	sf::RenderWindow& _window;
	sf::Font _font;
};

