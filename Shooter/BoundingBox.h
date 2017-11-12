#pragma once

#include <memory>
#include <vector>

#include "Projection.h"
#include "Vector2.h"

class BoundingBox {
public:
	BoundingBox(Vector2& position, int width, int height, double orientation);

public:
	bool intersects(BoundingBox& boundingBox);
	Projection project(Vector2& axis);

private:
	std::vector<std::shared_ptr<Vector2>> _vertices;
	std::vector<std::shared_ptr<Vector2>> _normals;
};