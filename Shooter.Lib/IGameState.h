#pragma once

#include "IGameSet.h"

#include "Camera.h"
#include "Crosshair.h"
#include "Player.h"

class IGameState {
public:
	virtual Camera& getCamera() = 0;
	virtual Crosshair& getCrosshair() = 0;
	virtual IGameSet& getGameSet() const = 0;
	virtual Player& getPlayer() const = 0;
};