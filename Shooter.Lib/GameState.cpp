#include "BoundingBox.h"
#include "Event.h"
#include "Firearm.h"
#include "GameState.h"
#include "IGameSettings.h"
#include "IInputManager.h"

GameState::GameState(IGameSet& gameSet, IGameSettings& gameSettings, IInputManager& inputManager, Crosshair& crosshair, Player& player) :
	_crosshair(crosshair),
	_gameSet(gameSet),
	_gameSettings(gameSettings),
	_inputManager(inputManager),
	_isStopped(false),
	_player(player),
	_projectiles(),
	_selectedProp(NULL)
{
	std::shared_ptr<Firearm> firearm = std::make_shared<Firearm>(20, 10, 1000, 120);
	_player.equipWeapon(firearm);
}

Vector2 GameState::getPlayerAcceleration() {
	Vector2 acceleration;
	if (_inputManager.isKeyDown(UP)) {
		acceleration.y--;
	}

	if (_inputManager.isKeyDown(DOWN)) {
		acceleration.y++;
	}

	if (_inputManager.isKeyDown(LEFT)) {
		acceleration.x--;
	}

	if (_inputManager.isKeyDown(RIGHT)) {
		acceleration.x++;
	}

	acceleration.normalize();
	acceleration.multiply(_gameSettings.getAccelerationNorm());

	return acceleration;
}

void GameState::processInput()
{
	Vector2 acceleration = getPlayerAcceleration();
	_player.setAcceleration(acceleration);

	double mouseX, mouseY;
	_inputManager.getMouseState(mouseX, mouseY);

	Vector2& crosshairPosition = _crosshair.getPosition();
	crosshairPosition.x = mouseX;
	crosshairPosition.y = mouseY;

	Event event;
	while (_inputManager.pollEvent(event)) {
		EventType eventType = event.getType();

		switch (eventType)
		{
		case MOUSE_BUTTON_DOWN:
			handleMouseButtonDown();
			break;

		case QUIT:
			_isStopped = true;
			break;

		default:
			break;
		}
	}
}

void GameState::update(sf::Time elapsedTime)
{
	Vector2& crosshairPosition = _crosshair.getPosition();

	_player.pointAt(crosshairPosition);

	std::shared_ptr<Prop> selectedProp = _gameSet.getPropAt(crosshairPosition);
	if (selectedProp == NULL) {
		if (_selectedProp != NULL) {
			_selectedProp->setSelected(false);
			_selectedProp = NULL;
		}
	}
	else if (selectedProp != _selectedProp) {
		if (_selectedProp != NULL) {
			_selectedProp->setSelected(false);
		}

		selectedProp->setSelected(true);
		_selectedProp = selectedProp;
	}

	BoundingBox playerBoundingBox = _player.getBoundingBox(elapsedTime);

	if (_gameSet.collidesWith(playerBoundingBox)) {
		_player.immobilize();
	}
	else {
		_player.move(elapsedTime);
		_camera.setPosition(_player.getPosition());
	}

	for each (std::shared_ptr<Projectile> projectile in _projectiles)
	{
		BoundingBox projectileBoundingBox = projectile->getBoundingBox(elapsedTime);

		if (_gameSet.collidesWith(projectileBoundingBox)) {
			// TODO
		}
		else if (projectileBoundingBox.intersects(playerBoundingBox)) {
			// TODO
		}

		projectile->move(elapsedTime);
	}
}

Camera& GameState::getCamera() {
	return _camera;
}

Crosshair& GameState::getCrosshair()
{
	return _crosshair;
}

IGameSet& GameState::getGameSet() const
{
	return _gameSet;
}

Player& GameState::getPlayer() const {
	return _player;
}

std::vector<std::shared_ptr<Projectile>>& GameState::getProjectiles() {
	return _projectiles;
}

void GameState::handleMouseButtonDown()
{
	if (_player.canAttack()) {
		double mouseX, mouseY;
		_inputManager.getMouseState(mouseX, mouseY);

		Vector2& crosshairPosition = _crosshair.getPosition();
		std::vector<std::shared_ptr<Projectile>> projectiles = _player.attackToward(crosshairPosition);

		for each (std::shared_ptr<Projectile> projectile in projectiles)
		{
			_projectiles.push_back(projectile);
		}
	}
}

bool GameState::isStopped()
{
	return _isStopped;
}
