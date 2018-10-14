#pragma once

#include "GameSettings.h"

using namespace Shooter::Input;

GameSettings::GameSettings() {
}

double GameSettings::getAccelerationNorm() const {
	return 1000;
}