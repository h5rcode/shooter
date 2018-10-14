#pragma once

#include <string>

struct LevelItemDescriptor {
public:
	std::string itemId;
	double x;
	double y;
	double orientation;
	std::string texture;
};