#include "SfmlRenderer.h"

#include <SFML/Graphics.hpp>

#include <sstream>

#include "Crosshair.h"
#include "Wall.h"

SfmlRenderer::SfmlRenderer(IGameState& gameState, sf::RenderWindow& window) :
	_gameState(gameState),
	_window(window),
	_font()
{
	_font.loadFromFile("Resources/fonts/arial.ttf");
}

void SfmlRenderer::render() {
	_window.clear();

	IGameSet& gameSet = _gameState.getGameSet();
	Camera& camera = _gameState.getCamera();
	Player& player = _gameState.getPlayer();
	Crosshair& crosshair = _gameState.getCrosshair();

	Vector2 cameraPosition = camera.getPosition();

	sf::View view;
	view.setCenter(sf::Vector2f((float)cameraPosition.x, (float)cameraPosition.y));
	view.setSize(sf::Vector2f((float)camera.getViewWidth(), (float)camera.getViewHeight()));

	_window.setView(view);

	gameSet.render(_window);
	player.render(_window);
	crosshair.render(_window);

	renderHud();

	_window.setView(view);

	_window.display();
}

void SfmlRenderer::renderHud() {
	Player& player = _gameState.getPlayer();
	Crosshair& crosshair = _gameState.getCrosshair();
	Vector2 crosshairPosition = crosshair.getPosition();
	Vector2 playerSpeed = player.getSpeed();

	std::stringstream stream;
	stream << "Crosshair (" << crosshairPosition.x << ", " << crosshairPosition.y << ")";
	stream << std::endl;
	stream << "Orientation = " << player.getOrientation();
	stream << std::endl;
	stream << "Speed (" << playerSpeed.x << ", " << playerSpeed.y << ")";
	stream << std::endl;
	stream << "Speed norm = " << playerSpeed.getNorm();

	sf::Text text;
	text.setFont(_font);
	text.setScale(0.5f, 0.5f);
	text.setFillColor(sf::Color::White);
	text.setString(stream.str());

	sf::View defaultView = _window.getDefaultView();
	_window.setView(defaultView);

	_window.draw(text);

}
