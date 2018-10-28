#include "SfmlRenderer.h"

#include <SFML/Graphics.hpp>

#include <memory>
#include <sstream>
#include <vector>

#include "Crosshair.h"
#include "Projectile.h"
#include "Wall.h"

using namespace Shooter::Inventory;
using namespace Shooter::Math;
using namespace Shooter::Rendering;

SfmlRenderer::SfmlRenderer(
	IGameState& gameState,
	IPlayerRenderer& playerRenderer,
	IProjectileRenderer& projectileRenderer,
	sf::RenderWindow& window,
	IResourceManager& resourceManager) :
	_gameState(gameState),
	_playerRenderer(playerRenderer),
	_projectileRenderer(projectileRenderer),
	_window(window),
	_resourceManager(resourceManager)
{
	sf::Font* hudFont = _resourceManager.getFont("Resources/fonts/arial.ttf");
	_font = *hudFont;
}

void SfmlRenderer::render(sf::Time elapsedTime) {
	_window.clear();

	IGameSet& gameSet = _gameState.getGameSet();
	Camera& camera = _gameState.getCamera();
	IPlayer& player = _gameState.getPlayer();
	Crosshair& crosshair = _gameState.getCrosshair();

	Vector2 cameraPosition = camera.getPosition();

	sf::View view;
	view.setCenter(sf::Vector2f((float)cameraPosition.x, (float)cameraPosition.y));
	view.setSize(sf::Vector2f((float)camera.getViewWidth(), (float)camera.getViewHeight()));

	_window.setView(view);

	gameSet.render(_window);

	_playerRenderer.render(player, elapsedTime);

	std::vector<std::shared_ptr<Projectile>>& projectiles = _gameState.getProjectiles();
	for each (std::shared_ptr<Projectile> projectile in projectiles)
	{
		_projectileRenderer.render(*projectile);
	}

	crosshair.render(_window);

	renderHud();

	_window.setView(view);

	_window.display();
}

void SfmlRenderer::renderHud() {
	IPlayer& player = _gameState.getPlayer();
	IInventory& inventory = player.getInventory();
	Crosshair& crosshair = _gameState.getCrosshair();
	Vector2 crosshairPosition = crosshair.getPosition();
	Vector2 playerSpeed = player.getSpeed();

	std::stringstream stream;
	stream << "Crosshair (" << crosshairPosition.x << ", " << crosshairPosition.y << ")" << std::endl;
	stream << "Orientation = " << player.getOrientation() << std::endl;
	stream << "Speed (" << playerSpeed.x << ", " << playerSpeed.y << ")" << std::endl;
	stream << "Speed norm = " << playerSpeed.getNorm() << std::endl;
	stream << "Weight = " << inventory.getCurrentWeight() << "/" << inventory.getMaxWeight() << std::endl;

	std::shared_ptr<IWeapon> equipedWeapon = player.getEquipedWeapon();
	if (equipedWeapon != NULL) {
		stream << equipedWeapon->getDescription();
		stream << std::endl;
	}

	sf::Text text;
	text.setFont(_font);
	text.setScale(0.5f, 0.5f);
	text.setFillColor(sf::Color::White);
	text.setString(stream.str());

	sf::View defaultView = _window.getDefaultView();
	_window.setView(defaultView);
	_window.draw(text);
}
