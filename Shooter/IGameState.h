#pragma once

#include "IGameSet.h"
#include "Player.h"

class IGameState {
public:
	virtual IGameSet& getGameSet() const = 0;
	virtual Player& getPlayer() const = 0;
};