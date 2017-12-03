#pragma once

#include "IGameSettings.h"

class GameSettings : public IGameSettings {
public:
	GameSettings();

public:
	double getAccelerationNorm() const;
};