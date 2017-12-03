#pragma once

#include <string>

#include "BoundingBox.h"
#include "Vector2.h"

class Prop {
public:
	Prop(Vector2 position, int width, int height, double orientation, std::string& texture);
public:
	BoundingBox& getBoundingBox();
	Vector2& getPosition();
	std::string& getTexture();
private:
	BoundingBox _boundingBox;
	Vector2 _position;
	std::string& _texture;
};