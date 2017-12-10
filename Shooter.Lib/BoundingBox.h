#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Projection.h"
#include "Vector2.h"

class BoundingBox {
public:
	BoundingBox(Vector2& position, int width, int height, double orientation);

public:
	std::vector<std::shared_ptr<Vector2>>& getNormals();
	bool intersects(BoundingBox& boundingBox) const;
	Projection project(Vector2& axis) const;
	void render(sf::RenderWindow& window);

private:
	std::vector<std::shared_ptr<Vector2>> _vertices;
	std::vector<std::shared_ptr<Vector2>> _normals;
};