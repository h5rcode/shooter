#define _USE_MATH_DEFINES

#include "SfmlRenderer.h"

#include <SFML/Graphics.hpp>

#include <math.h>
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

	render(gameSet);
	player.render(_window);
	render(crosshair);

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

void SfmlRenderer::render(IGameSet& gameSet) {
	std::vector<std::shared_ptr<Wall>>& walls = gameSet.getWalls();

	for (std::vector<std::shared_ptr<Wall>>::iterator it = walls.begin(); it != walls.end(); ++it)
	{
		std::shared_ptr<Wall> wall = *it;
		wall->render(_window);
	}
}

void SfmlRenderer::render(Crosshair& crosshair)
{
	Vector2& position = crosshair.getPosition();
	std::string& texture = crosshair.getTexture();
	double orientation = 0;
	render(texture, position, orientation);
}

void SfmlRenderer::render(Prop & prop)
{
	Vector2& position = prop.getPosition();
	std::string& texture = prop.getTexture();
	render(texture, position, 0);
}

void SfmlRenderer::render(std::string &texture, Vector2 & position, double orientation)
{
	sf::Texture sfmlTexture;
	sfmlTexture.loadFromFile(texture.c_str());

	sf::Vector2u sfmlTextureSize = sfmlTexture.getSize();

	int angle = -180 * (orientation - M_PI_2) / M_PI;

	sf::Sprite sprite;
	sprite.setTexture(sfmlTexture);
	sprite.setPosition(position.x, position.y);
	sprite.setOrigin(sfmlTextureSize.x / 2, sfmlTextureSize.y / 2);
	sprite.setRotation(angle);

	_window.draw(sprite);
}

void SfmlRenderer::quit() {
}
