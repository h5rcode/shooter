#include "BoundingBox.h"
#include "Event.h"
#include "GameState.h"
#include "IGameSettings.h"
#include "IInputManager.h"

GameState::GameState(IGameSet& gameSet, IGameSettings& gameSettings, IInputManager& inputManager, Crosshair& crosshair, Player& player) :
	_isStopped(false),
	_gameSet(gameSet),
	_gameSettings(gameSettings),
	_inputManager(inputManager),
	_crosshair(crosshair),
	_player(player)
{
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

	int mouseX, mouseY;
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

	BoundingBox boundingBox = _player.getBoundingBox(elapsedTime);

	if (_gameSet.collidesWith(boundingBox) == false) {
		_player.move(elapsedTime);
		_camera.setPosition(_player.getPosition());
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

void GameState::handleMouseButtonDown()
{
	if (_player.canAttack()) {
		int mouseX, mouseY;
		_inputManager.getMouseState(mouseX, mouseY);

		Vector2& crosshairPosition = _crosshair.getPosition();
		std::shared_ptr<IWeapon> weapon = _player.getEquipedWeapon();
	}
}

bool GameState::isStopped()
{
	return _isStopped;
}
