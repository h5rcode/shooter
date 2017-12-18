#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "Crosshair.h"
#include "IGameSet.h"
#include "IGameSettings.h"
#include "IGameState.h"
#include "IInputManager.h"
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
	bool isStopped();
	void processInput();
	void update(sf::Time elapsedTime);

private:
	Vector2 getPlayerAcceleration();
	void handleMouseButtonDown();

private:
	std::shared_ptr<Prop> _selectedProp;
	bool _isStopped;
	Camera _camera;
	Crosshair _crosshair;
	IGameSet& _gameSet;
	IGameSettings& _gameSettings;
	IInputManager& _inputManager;
	Player& _player;
};
