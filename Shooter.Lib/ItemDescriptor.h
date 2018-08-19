#pragma once

#include <string>

struct ItemDescriptor {
public:
	std::string itemId;
	double x;
	double y;
	double orientation;
	std::string texture;
};