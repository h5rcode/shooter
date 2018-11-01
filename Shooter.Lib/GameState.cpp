#include "BoundingBox.h"
#include "Event.h"
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
	IInputManager& inputManager,
	Crosshair& crosshair,
	IPlayer& player,
	Camera& camera) :
	_camera(camera),
	_crosshair(crosshair),
	_gameSet(gameSet),
	_gameSettings(gameSettings),
	_inputManager(inputManager),
	_isStopped(false),
	_player(player),
	_projectiles(),
	_selectedProp(NULL)
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
		case LEFT_BUTTON_CLICKED:
			handleMouseButtonDown();
			break;

		case RIGHT_BUTTON_CLICKED:
			handleUseEvent();
			break;

		case DROP_PROP:
			handleDropPropEvent();
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
	setSelectedItem(crosshairPosition);
	setSelectedProp(crosshairPosition);

	BoundingBox playerBoundingBox = _player.getBoundingBox(elapsedTime);

	if (_gameSet.collidesWith(playerBoundingBox)) {
		_player.immobilize();

		GameEvent gameEvent{ GameEventType::PlayerImmobilized };
		_gameEvents.push_back(gameEvent);
	}
	else {
		_player.move(elapsedTime);
		_camera.setPosition(_player.getPosition());
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
		}
		else if (projectileBoundingBox.intersects(playerBoundingBox)) {
			_player.hurt(projectile->getDamage());
			eraseProjectile = true;

			GameEvent gameEvent{ GameEventType::PlayerHurt };
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

void GameState::handleDropPropEvent() {
	std::shared_ptr<Prop> prop = _player.getProp();
	if (prop != NULL) {
		Vector2 crosshairPosition = _crosshair.getPosition();
		BoundingBox& propBoundingBox = prop->getBoundingBox();
		BoundingBox targetPropBoundingBox = BoundingBox(crosshairPosition, propBoundingBox.getWidth(), propBoundingBox.getHeight(), _player.getOrientation());

		if (_gameSet.collidesWith(targetPropBoundingBox) == false) {
			_player.dropProp();
			prop->setOrientation(_player.getOrientation());
			prop->setPosition(crosshairPosition);

			_gameSet.addProp(prop);
		}
	}
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

		GameEvent gameEvent{ GameEventType::PlayerAttacked };
		_gameEvents.push_back(gameEvent);
	}
}

void GameState::handleUseEvent() {
	if (_selectedItem != NULL) {
		bool itemWasPickedUp = _player.pickUpItem(_selectedItem);

		if (itemWasPickedUp) {
			GameEvent gameEvent{ GameEventType::PlayerPickedUpItem };
			_gameEvents.push_back(gameEvent);

			_gameSet.removeItem(_selectedItem);

			std::shared_ptr<IWeapon> weapon = std::dynamic_pointer_cast<IWeapon>(_selectedItem);
			if (weapon != NULL && _player.getEquipedWeapon() == NULL) {
				_player.equipWeapon(weapon);
			}

			_selectedItem = NULL;
		}
	}
}

bool GameState::isStopped()
{
	return _isStopped;
}

void GameState::setSelectedItem(Vector2& crosshairPosition) {
	std::shared_ptr<IItem> selectedItem = _gameSet.getItemAt(crosshairPosition);
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

void GameState::setSelectedProp(Vector2& crosshairPosition) {
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
}
