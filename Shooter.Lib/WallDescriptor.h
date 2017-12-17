#pragma once

#include <string>

struct WallDescriptor {
public:
	std::string texture;
	double x;
	double y;
	double orientation;
	int width;
	int length;
};