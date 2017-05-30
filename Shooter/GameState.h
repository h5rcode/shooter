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
	GameState(IGameSet& gameSet, IGameSettings& gameSettings, IInputManager& inputManager, Crosshair& crosshair, Player& player);

	Vector2& getCamera();
	Crosshair& getCrosshair();
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
	Vector2 _camera;
	Crosshair _crosshair;
	IGameSet& _gameSet;
	IGameSettings& _gameSettings;
	IInputManager& _inputManager;
	Player& _player;
};

