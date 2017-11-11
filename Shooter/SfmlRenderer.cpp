#include "SfmlRenderer.h"

#include <SFML/Graphics.hpp>

#include <sstream>

#include "Crosshair.h"
#include "Wall.h"

SfmlRenderer::SfmlRenderer(IGameState& gameState, sf::RenderWindow& window) :
	_gameState(gameState),
	_window(window)
{
}

void SfmlRenderer::render() {
	_window.clear();

	IGameSet& gameSet = _gameState.getGameSet();
	Camera& camera = _gameState.getCamera();
	Player& player = _gameState.getPlayer();
	Crosshair& crosshair = _gameState.getCrosshair();

	Vector2 cameraPosition = camera.getPosition();

	sf::View view;
	view.setCenter(sf::Vector2f(cameraPosition.x, cameraPosition.y));
	view.setSize(sf::Vector2f(camera.getViewWidth(), camera.getViewHeight()));

	_window.setView(view);

	gameSet.render(_window);
	player.render(_window);
	crosshair.render(_window);

	renderHud();

	_window.setView(view);

	_window.display();
}

void SfmlRenderer::renderHud() {
	Crosshair& crosshair = _gameState.getCrosshair();
	Vector2 crosshairPosition = crosshair.getPosition();

	std::stringstream stream;
	stream << "Crosshair (" << crosshairPosition.x << ", " << crosshairPosition.y << ")";

	sf::Font font;
	font.loadFromFile("Resources/fonts/arial.ttf");

	sf::Text text;
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setString(stream.str());

	sf::View defaultView = _window.getDefaultView();
	_window.setView(defaultView);

	_window.draw(text);

}
