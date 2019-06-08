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
	std::vector<std::shared_ptr<INonPlayingCharacter>>& nonPlayingCharacters,
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
	for each (std::shared_ptr<INonPlayingCharacter> nonPlayingCharacter in nonPlayingCharacters)
	{
		_nonPlayingCharacters.push_back(nonPlayingCharacter);
	}
}

PlayerMovementState& GameState::getPlayerMovementState()
{
	return _playerMovementState;
}

Camera& GameState::getCamera()
{
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

std::vector<std::shared_ptr<INonPlayingCharacter>>& GameState::getNonPlayingCharacters() {
	return _nonPlayingCharacters;
}

IPlayer& GameState::getPlayer() const
{
	return _player;
}

std::vector<std::shared_ptr<Projectile>>& GameState::getProjectiles()
{
	return _projectiles;
}

std::shared_ptr<IItem> GameState::getSelectedItem()
{
	return _selectedItem;
}

bool GameState::isStopped()
{
	return _isStopped;
}

void GameState::selectItemAtPosition(Vector2& position)
{
	std::shared_ptr<IItem> selectedItem = _gameSet.getItemAt(position);
	if (selectedItem == NULL)
	{
		if (_selectedItem != NULL)
		{
			_selectedItem->setSelected(false);
			_selectedItem = NULL;
		}
	}
	else if (selectedItem != _selectedItem)
	{
		if (_selectedItem != NULL)
		{
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

void GameState::stop()
{
	_isStopped = true;
}

std::vector<GameEvent> GameState::update(sf::Time elapsedTime, std::vector<sf::Event>& events)
{
	std::vector<GameEvent> gameEvents;
	for each (sf::Event event in events)
	{
		std::vector<GameEvent> newGameEvents = _inputEventHandler.handle(*this, event);
		for each (GameEvent newGameEvent in newGameEvents)
		{
			gameEvents.push_back(newGameEvent);
		}
	}

	Vector2& crosshairPosition = _crosshair.getPosition();
	_inputManager.getMouseState(crosshairPosition.x, crosshairPosition.y);

	Vector2 acceleration;
	if (_playerMovementState.up) {
		acceleration.y--;
	}

	if (_playerMovementState.down) {
		acceleration.y++;
	}

	if (_playerMovementState.left) {
		acceleration.x--;
	}

	if (_playerMovementState.right) {
		acceleration.x++;
	}

	acceleration.normalize();
	acceleration.multiply(_gameSettings.getAccelerationNorm());
	_player.setAcceleration(acceleration);
	_player.updateSpeed(elapsedTime);

	_player.pointAt(crosshairPosition);
	selectItemAtPosition(crosshairPosition);

	BoundingBox playerBoundingBox = _player.getBoundingBox(elapsedTime);

	Vector2 initialSpeed = _player.getSpeed();

	bool collidesWithNpc = false;
	for each (std::shared_ptr<INonPlayingCharacter> npc in _nonPlayingCharacters)
	{
		collidesWithNpc = npc->getBoundingBox(elapsedTime).intersects(playerBoundingBox);
		if (collidesWithNpc) {
			break;
		}
	}

	Vector2& playerCurrentPosition = _player.getPosition();
	Vector2 playerNextPosition = _player.computePosition(elapsedTime);

	std::vector<std::shared_ptr<Collision>> collisions = _gameSet.computeCollisionsWithSegment(playerCurrentPosition, playerNextPosition);

	if (collidesWithNpc) {
		_player.immobilize();
	}
	else {
		for each (std::shared_ptr<Collision> collision in collisions) {
			_player.collide(collision->normal);
		}

		_player.move(elapsedTime);
		_camera.setPosition(_player.getPosition());
	}

	Vector2& newSpeed = _player.getSpeed();
	Vector2 zeroSpeed;
	if (initialSpeed == zeroSpeed && newSpeed != initialSpeed)
	{
		gameEvents.push_back(GameEvent{ GameEventType::PlayerStartedMoving });
	}
	else if (initialSpeed != zeroSpeed && newSpeed == zeroSpeed)
	{
		gameEvents.push_back(GameEvent{ GameEventType::PlayerStoppedMoving });
	}

	std::vector<std::shared_ptr<Projectile>>::iterator projectileIterator = _projectiles.begin();
	while (projectileIterator != _projectiles.end())
	{
		std::shared_ptr<Projectile> projectile = *projectileIterator;
		BoundingBox projectileBoundingBox = projectile->getBoundingBox(elapsedTime);

		bool eraseProjectile = false;
		if (_gameSet.collidesWith(projectileBoundingBox))
		{
			// TODO Handle projectiles that are outside the game set.
			eraseProjectile = true;

			GameEvent gameEvent;
			gameEvent.Type = GameEventType::ProjectileImpact;
			gameEvent.ProjectileImpact = ProjectileImpactEvent{ projectile };
			gameEvents.push_back(gameEvent);
		}
		else if (projectileBoundingBox.intersects(playerBoundingBox))
		{
			int damage = projectile->getDamage();
			_player.hurt(damage);
			eraseProjectile = true;

			GameEvent gameEvent;
			gameEvent.Type = GameEventType::PlayerHurt;
			gameEvent.PlayerHurt = PlayerHurtEvent{ damage };
			gameEvents.push_back(gameEvent);
		}
		else {
			for each (std::shared_ptr<INonPlayingCharacter> npc in _nonPlayingCharacters)
			{
				BoundingBox npcBoundingBox = npc->getBoundingBox(elapsedTime);
				if (projectileBoundingBox.intersects(npcBoundingBox)) {
					int damage = projectile->getDamage();
					npc->hurt(damage);
					eraseProjectile = true;
				}
			}
		}

		if (eraseProjectile)
		{
			projectileIterator = _projectiles.erase(projectileIterator);
		}
		else
		{
			++projectileIterator;
			projectile->move(elapsedTime);
		}
	}

	return gameEvents;
}
