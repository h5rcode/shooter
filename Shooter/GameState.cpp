#include "GameState.h"

#include "Event.h"
#include "IGameSettings.h"
#include "IInputManager.h"

GameState::GameState(IGameSet& gameSet, IGameSettings& gameSettings, IInputManager& inputManager, Player& player) :
	_isStopped(false),
	_gameSet(gameSet),
	_gameSettings(gameSettings),
	_inputManager(inputManager),
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

	Event event;
	while (_inputManager.pollEvent(&event)) {
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

void GameState::update(int elapsed)
{
	_player.move(elapsed);
}

IGameSet& GameState::getGameSet() const {
	return _gameSet;
}

Player& GameState::getPlayer() const {
	return _player;
}

void GameState::handleMouseButtonDown() {
	if (_player.canAttack()) {
		int mouseX, mouseY;
		_inputManager.getMouseState(&mouseX, &mouseY);

		Vector2* crosshairPosition = _crosshair.getPosition();
		IWeapon* weapon = _player.getEquipedWeapon();
	}
}

bool GameState::isStopped() {
	return _isStopped;
}
