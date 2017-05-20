#pragma once

class IGameSettings {
public:
	virtual double getAccelerationNorm() const = 0;
};