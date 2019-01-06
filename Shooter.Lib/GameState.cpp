#include "BoundingBox.h"
#include "GameState.h"
#include "IGameSettings.h"
#include "IInputManager.h"

using namespace Shooter::Input;
using namespace Shooter::Items;
using namespace Shooter::Items::Weapons;
using namespace Shooter::Math;
using namespace Shooter::World;

GameState::GameState(
	IGameSet& gameSet,
	IGameSettings& gameSettings,
	IInputEventHandler& inputEventHandler,
	IInputManager& inputManager,
	Crosshair& crosshair,
	IPlayer& player,
	Camera& camera) :
	_camera(camera),
	_crosshair(crosshair),
	_gameSet(gameSet),
	_gameSettings(gameSettings),
	_inputManager(inputManager),
	_inputEventHandler(inputEventHandler),
	_isStopped(false),
	_player(player),
	_projectiles()
{
}

Vector2& GameState::getPlayerMovementState() {
	return _playerMovementState;
}

void GameState::processInput()
{
	sf::Event event;
	while (_inputManager.pollEvent(event)) {
		std::vector<GameEvent> newGameEvents = _inputEventHandler.handle(*this, event);
		for each (GameEvent newGameEvent in newGameEvents)
		{
			_gameEvents.push_back(newGameEvent);
		}
	}
}

void GameState::update(sf::Time elapsedTime)
{
	Vector2& crosshairPosition = _crosshair.getPosition();
	_inputManager.getMouseState(crosshairPosition.x, crosshairPosition.y);

	Vector2 acceleration = _playerMovementState;
	acceleration.normalize();
	acceleration.multiply(_gameSettings.getAccelerationNorm());
	_player.setAcceleration(acceleration);

	_player.pointAt(crosshairPosition);
	selectItemAtPosition(crosshairPosition);

	BoundingBox playerBoundingBox = _player.getBoundingBox(elapsedTime);

	Vector2 initialSpeed = _player.getSpeed();
	if (_gameSet.collidesWith(playerBoundingBox)) {
		_player.immobilize();
	}
	else {
		_player.move(elapsedTime);
		_camera.setPosition(_player.getPosition());
	}

	Vector2 newSpeed = _player.getSpeed();
	Vector2 zeroSpeed;
	if (initialSpeed == zeroSpeed && newSpeed != initialSpeed) {
		_gameEvents.push_back(GameEvent{ GameEventType::PlayerStartedMoving });
	}
	else if (initialSpeed != zeroSpeed && newSpeed == zeroSpeed) {
		_gameEvents.push_back(GameEvent{ GameEventType::PlayerStoppedMoving });
	}

	std::vector<std::shared_ptr<Projectile>>::iterator projectileIterator = _projectiles.begin();
	while (projectileIterator != _projectiles.end())
	{
		std::shared_ptr<Projectile> projectile = *projectileIterator;
		BoundingBox projectileBoundingBox = projectile->getBoundingBox(elapsedTime);

		bool eraseProjectile = false;
		if (_gameSet.collidesWith(projectileBoundingBox)) {
			// TODO Handle projectiles that are outside the game set.
			eraseProjectile = true;

			GameEvent gameEvent;
			gameEvent.Type = GameEventType::ProjectileImpact;
			gameEvent.ProjectileImpact = ProjectileImpactEvent{ projectile };
			_gameEvents.push_back(gameEvent);
		}
		else if (projectileBoundingBox.intersects(playerBoundingBox)) {
			int damage = projectile->getDamage();
			_player.hurt(damage);
			eraseProjectile = true;

			GameEvent gameEvent;
			gameEvent.Type = GameEventType::PlayerHurt;
			gameEvent.PlayerHurt = PlayerHurtEvent{ damage };
			_gameEvents.push_back(gameEvent);
		}

		if (eraseProjectile) {
			projectileIterator = _projectiles.erase(projectileIterator);
		}
		else {
			++projectileIterator;
			projectile->move(elapsedTime);
		}
	}
}

Camera& GameState::getCamera() {
	return _camera;
}

Crosshair& GameState::getCrosshair()
{
	return _crosshair;
}

std::vector<GameEvent>& GameState::getGameEvents() {
	return _gameEvents;
}

IGameSet& GameState::getGameSet() const
{
	return _gameSet;
}

IPlayer& GameState::getPlayer() const {
	return _player;
}

std::vector<std::shared_ptr<Projectile>>& GameState::getProjectiles() {
	return _projectiles;
}

std::shared_ptr<IItem> GameState::getSelectedItem() {
	return _selectedItem;
}

bool GameState::isStopped()
{
	return _isStopped;
}

void GameState::selectItemAtPosition(Vector2& position) {
	std::shared_ptr<IItem> selectedItem = _gameSet.getItemAt(position);
	if (selectedItem == NULL) {
		if (_selectedItem != NULL) {
			_selectedItem->setSelected(false);
			_selectedItem = NULL;
		}
	}
	else if (selectedItem != _selectedItem) {
		if (_selectedItem != NULL) {
			_selectedItem->setSelected(false);
		}

		selectedItem->setSelected(true);
		_selectedItem = selectedItem;
	}
}

void GameState::setSelectedItem(std::shared_ptr<IItem> selectedItem)
{
	_selectedItem = selectedItem;
}

void GameState::stop() {
	_isStopped = true;
}
