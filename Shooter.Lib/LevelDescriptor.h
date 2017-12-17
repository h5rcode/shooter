#pragma once

#include <memory>
#include <string>
#include <vector>

#include "PropDescriptor.h"
#include "WallDescriptor.h"

struct LevelDescriptor {
	std::string name;
	std::vector<std::shared_ptr<PropDescriptor>> props;
	std::vector<std::shared_ptr<WallDescriptor>> walls;

	void loadFromFile(std::string& fileName);
};