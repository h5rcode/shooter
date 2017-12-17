#pragma once

#include <string>

struct WallDescriptor {
	std::string texture;
	double x;
	double y;
	double orientation;
	int width;
	int length;
};