#include "SfmlRenderer.h"

#include <SFML/Graphics.hpp>

#include <sstream>

#include "Crosshair.h"
#include "Wall.h"

SfmlRenderer::SfmlRenderer(sf::RenderWindow& window) :
	_window(window)
{
}

void SfmlRenderer::render(IGameState& gameState) {
	_window.clear();

	sf::Font font;
	font.loadFromFile("Resources/fonts/arial.ttf");

	IGameSet& gameSet = gameState.getGameSet();
	Camera& camera = gameState.getCamera();
	Player& player = gameState.getPlayer();
	Crosshair& crosshair = gameState.getCrosshair();

	Vector2 cameraPosition = camera.getPosition();

	sf::View view;
	view.setCenter(sf::Vector2f(cameraPosition.x, cameraPosition.y));
	view.setSize(sf::Vector2f(camera.getViewWidth(), camera.getViewHeight()));

	_window.setView(view);

	gameSet.render(_window);
	player.render(_window);
	crosshair.render(_window);

	Vector2 crosshairPosition = crosshair.getPosition();

	std::stringstream stream;
	stream << "Crosshair (" << crosshairPosition.x << ", " << crosshairPosition.y << ")";

	sf::Text text;
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setString(stream.str());

	_window.draw(text);

	_window.display();
}

void SfmlRenderer::quit() {
}
