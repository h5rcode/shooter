#pragma once

#include <SFML/Graphics.hpp>

#include "IRenderer.h"
#include "Prop.h"

class SfmlRenderer : public IRenderer
{
public:
	SfmlRenderer(sf::RenderWindow& window);

	void render(IGameState& gameState);
	void quit();

private:
	sf::RenderWindow& _window;

private:
	void render(IGameSet& gameSet);
	void render(Crosshair& crosshair);
	void render(Prop& prop);
	void render(std::string &texture, Vector2 & position, double orientation);
};

