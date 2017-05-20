#pragma once

#include "Crosshair.h"
#include "IGameSet.h"
#include "IGameSettings.h"
#include "IGameState.h"
#include "IInputManager.h"
#include "Player.h"

class GameState : public IGameState
{
public:
	GameState(IGameSet& gameSet, IGameSettings& gameSettings, IInputManager& inputManager, Player& player);

	IGameSet& getGameSet() const;
	Player& getPlayer() const;
	bool isStopped();
	void processInput();
	void update(int elapsed);

private:
	Vector2 getPlayerAcceleration();
	void handleMouseButtonDown();

private:
	bool _isStopped;
	Crosshair _crosshair;
	IGameSet& _gameSet;
	IGameSettings& _gameSettings;
	IInputManager& _inputManager;
	Player& _player;
};

