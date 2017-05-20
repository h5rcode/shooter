#pragma once

#include "IGameState.h"

class IRenderer {

public:
	virtual void render(IGameState& gameState) = 0;
	virtual void quit() = 0;
};