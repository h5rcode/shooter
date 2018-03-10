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
#include "Projectile.h"
#include "Player.h"
#include "Prop.h"

class GameState : public IGameState
{
public:
	GameState(IGameSet& gameSet, IGameSettings& gameSettings, IInputManager& inputManager, Crosshair& crosshair, Player& player);

	Camera& getCamera();
	Crosshair& getCrosshair();
	IGameSet& getGameSet() const;
	Player& getPlayer() const;
	std::vector<std::shared_ptr<Projectile>>& getProjectiles();
	bool isStopped();
	void processInput();
	void setSelectedProp(Vector2& crosshairPosition);
	void update(sf::Time elapsedTime);

private:
	Vector2 getPlayerAcceleration();
	void handleMouseButtonDown();
	void handleUseEvent();

private:
	std::shared_ptr<Prop> _selectedProp;
	bool _isStopped;
	Camera _camera;
	Crosshair _crosshair;
	IGameSet& _gameSet;
	IGameSettings& _gameSettings;
	IInputManager& _inputManager;
	Player& _player;
	std::vector<std::shared_ptr<Projectile>> _projectiles;
};
