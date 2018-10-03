#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "Crosshair.h"
#include "IGameSet.h"
#include "IGameSettings.h"
#include "IGameState.h"
#include "IInputManager.h"
#include "IPlayer.h"
#include "Projectile.h"
#include "Prop.h"

class GameState : public IGameState
{
public:
	GameState(
		IGameSet& gameSet,
		IGameSettings& gameSettings,
		IInputManager& inputManager,
		Crosshair& crosshair,
		IPlayer& player,
		Camera& camera);

	Camera& getCamera();
	Crosshair& getCrosshair();
	IGameSet& getGameSet() const;
	IPlayer& getPlayer() const;
	std::vector<std::shared_ptr<Projectile>>& getProjectiles();
	bool isStopped();
	void processInput();
	void setSelectedItem(Vector2& crosshairPosition);
	void setSelectedProp(Vector2& crosshairPosition);
	void update(sf::Time elapsedTime);

private:
	Vector2 getPlayerAcceleration();
	void handleDropPropEvent();
	void handleMouseButtonDown();
	void handleUseEvent();

private:
	std::shared_ptr<IItem> _selectedItem;
	std::shared_ptr<Prop> _selectedProp;
	bool _isStopped;
	Camera& _camera;
	Crosshair _crosshair;
	IGameSet& _gameSet;
	IGameSettings& _gameSettings;
	IInputManager& _inputManager;
	IPlayer& _player;
	std::vector<std::shared_ptr<Projectile>> _projectiles;
};
