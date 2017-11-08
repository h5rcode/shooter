#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "IRenderer.h"
#include "Wall.h"
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
	void render(Player& player);
	void render(Prop& prop);
	void render(Wall& wall);
	void render(std::string &texture, Vector2 & position, double orientation);
};

